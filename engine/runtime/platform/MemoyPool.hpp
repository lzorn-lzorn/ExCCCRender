#include "../../runtime/stdheader.h"

namespace ExCCCRender::Platform::MemoryPool {

#ifdef __APPLE__
    #define PAGE_SIZE 16384
    #define POOL_SIZE 16384
#else
    #define PAGE_SIZE 65536
    #define POOL_SIZE 65536
#endif
using namespace std::pmr;
/*
    64KB的内存:
    16,   32,   64,   128, 256, 512, 1024, 2048, 4096
    64*8  32*8  16*8  8*8  4*4  4*2  8     4     2

    16KB的内存同比缩小4倍
*/

static std::array<size_t, 9> block_size_table;
static std::array<size_t, 9> block_number_table;

namespace detail {
using _Block_Size = size_t;

struct MemoryBlock {
    bool         valid;   // 是否有效, 即是否存在使用者
    void*        data;    // 指向内存空间的链表
    void*        father;  // 记录使用者
    MemoryBlock* next;
    MemoryBlock* prev;

    enum class state {
        // 有效状态, 异常状态, 错误状态
        VALID,
        EXCEPTION,
        ERROR
    };

    MemoryBlock(size_t size, MemoryBlock* next = nullptr, MemoryBlock* prev = nullptr, void* father = nullptr)
        : next(next), prev(prev), father(father) {
        data = malloc(size);
        if (father) {
            valid = true;
        } else {
            valid = false;
        }
    }

    /*
        内存位于 available_list 所有的内存块的 father 均为 available_list
        内存位于 assigned_list 所有的内存块的 father 均为 对应引用它的位置
            - 既有 father 也有 valid 位, 说明该内存块正在被使用
            - father 和 valid 不一致时, 说明处于异常状态, 根据 father 重新设置 valid
            - father 和 valid 分别是 nullptr 和 false 时, 说明该内存处于野指针状态
    */
    state Check() {
        if (father || valid) {
            return state::VALID;
        } else if (father || !valid) {
            // father 存在, 但是valid位为无效位置
            valid = true;
            return state::EXCEPTION;
        } else if (!father || valid) {
            valid = false;
            return state::EXCEPTION;
        } else {
            return state::ERROR;
        }
    }

    MemoryBlock& Set(void* father, bool valid = true) {
        this->father = father;
        this->valid  = valid;
        return *this;
    }

    ~MemoryBlock() {
        free(data);
        next = nullptr;
        prev = nullptr;
    }
};

struct PoolTable {
public:
    MemoryBlock* available_list;  // 空闲内存块
    MemoryBlock* assigned_list;   // 已分配内存块

public:
    PoolTable(_Block_Size size, size_t number)
        : available_list(nullptr), assigned_list(nullptr), m_available_size(number), m_assigned_size(0), m_size(size) {
        init_block();
    }

    void* allocate(size_t bytes, size_t aligment = alignof(std::max_align_t)) {
    }

    void* deallocate(void* p, size_t bytes, size_t aligment = alignof(std::max_align_t)) {
    }

    ~PoolTable() {
        destory();
    }

    size_t GetAvailableSize() const noexcept {
        return m_available_size;
    }

    size_t GetAssignedSize() const noexcept {
        return m_assigned_size;
    }

    bool Check() const;

private:
    void init_block();
    void destory();

private:
    _Block_Size m_size;
    size_t      m_available_size;
    size_t      m_assigned_size;
};

class MemoryPoolImpl : public std::pmr::memory_resource {
public:
    explicit MemoryPoolImpl(std::pmr::memory_resource* upstream = std::pmr::get_default_resource())
        : m_upstream_allocator(upstream) {
        set_size_table();
        init_pool_table();
    }

    MemoryPoolImpl(const MemoryPoolImpl&)            = delete;
    MemoryPoolImpl& operator=(const MemoryPoolImpl&) = delete;

    virtual ~MemoryPoolImpl() {
    }

    void* allocate(size_t bytes, size_t aligment = alignof(std::max_align_t)) {
        return nullptr;
    }

    void* deallocate(void* p, size_t bytes, size_t aligment = alignof(std::max_align_t)) {
        return nullptr;
    }

    bool check() const {
        auto size = m_pools.size();
        for (size_t i = 0; i < size; ++i) {
            if (!m_pools[i]->Check()) {
                return false;
            }
        }
        return true;
    }

private:
    std::pmr::memory_resource* m_upstream_allocator;  // 封装系统原始 malloc
    std::array<PoolTable*, 9>  m_pools;

private:
    void set_size_table();  // 使用 block_size_table 初始化内存池
    void init_pool_table();
    void destory();

protected:
    // 返回一个指向所分配内存块的指针，内存块的大小至少为 bytes 字节，并满足 alignment 对齐要求
    // 如果实现无法满足这一要求，应抛出 std::bad_alloc。
    virtual void* do_allocate(std::size_t bytes, std::size_t alignment) override {
        return nullptr;
    }

    virtual void do_deallocate(void* p, size_t bytes, size_t alinment) override {
    }

    virtual bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override {
        return true;
    }
};
}  // namespace detail

class MemoryPool : public std::pmr::memory_resource {
public:
    MemoryPool() {
        InitMemoryPool();
    }

    ~MemoryPool() {
        // 析构资源
        m_pool = nullptr;
    }

    void* allocate(size_t bytes, size_t aligment = alignof(std::max_align_t)) {
        return nullptr;
    }

    void* deallocate(void* p, size_t bytes, size_t aligment = alignof(std::max_align_t)) {
        return nullptr;
    }

private:
    void InitMemoryPool() {
        m_pool = std::make_unique<detail::MemoryPoolImpl>();
    }

    // 只是负责监控内存而已
    void* do_allocate(std::size_t bytes, std::size_t alignment) override {
        void* ptr = m_pool->allocate(bytes, alignment);
        // 监控内存使用
        return ptr;
    }

    void do_deallocate(void* p, size_t bytes, size_t alignment) override {
        m_pool->deallocate(p, bytes, alignment);
    }

    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override {
        // 监控内存使用
        return other.is_equal(*m_pool);
    }

private:
    std::unique_ptr<detail::MemoryPoolImpl> m_pool;
};

}  // namespace ExCCCRender::Platform::MemoryPool
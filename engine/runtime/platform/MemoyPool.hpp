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
    void*        data;  // 指向内存空间的链表
    MemoryBlock* next;
    MemoryBlock* prev;

    MemoryBlock(size_t size, MemoryBlock* next = nullptr, MemoryBlock* prev = nullptr) : next(next), prev(prev) {
        data = malloc(size);
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
        : available_list(nullptr), assigned_list(nullptr), available_size(number), assigned_size(0), size(size) {
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
        return available_size;
    }

    size_t GetAssignedSize() const noexcept {
        return assigned_size;
    }

    bool check() const;

private:
    void init_block();
    void destory();

private:
    _Block_Size size;
    size_t      available_size;
    size_t      assigned_size;
};

class MemoryPoolImpl : public std::pmr::memory_resource {
public:
    explicit MemoryPoolImpl(std::pmr::memory_resource* upstream = std::pmr::get_default_resource())
        : upstream_allocator(upstream) {
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
        auto size = pools.size();
        for (size_t i = 0; i < size; ++i) {
            if (!pools[i]->check()) {
                return false;
            }
        }
        return true;
    }

private:
    std::pmr::memory_resource* upstream_allocator;  // 封装系统原始 malloc
    std::array<PoolTable*, 9>  pools;

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
        pool = nullptr;
    }

private:
    void InitMemoryPool() {
        pool = std::make_unique<detail::MemoryPoolImpl>();
    }

    // 只是负责监控内存而已
    void* do_allocate(std::size_t bytes, std::size_t alignment) override {
        void* ptr = pool->allocate(bytes, alignment);
        // 监控内存使用
        return ptr;
    }

    void do_deallocate(void* p, size_t bytes, size_t alignment) override {
        pool->deallocate(p, bytes, alignment);
    }

    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override {
        // 监控内存使用
        return other.is_equal(*pool);
    }

private:
    std::unique_ptr<detail::MemoryPoolImpl> pool;
};

}  // namespace ExCCCRender::Platform::MemoryPool
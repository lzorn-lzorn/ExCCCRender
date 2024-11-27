#include <cstddef>
#include "../../runtime/platform/MemoyPool.hpp"

namespace ExCCCRender::Platform::MemoryPool {

namespace detail {
void MemoryPoolImpl::set_size_table() {
    block_size_table   = {16, 32, 64, 128, 256, 512, 1024, 2048, 4096};
    block_number_table = {512, 256, 128, 64, 16, 8, 8, 4, 2};
}

void MemoryPoolImpl::init_pool_table() {
    std::allocator<detail::PoolTable> pool_table_allocator;
    auto                              table_size = block_size_table.size();
    for (size_t i = 0; i < table_size; i++)
        try {
            m_pools[i] = pool_table_allocator.allocate(1);
            std::construct_at(m_pools[i], block_size_table[i], block_number_table[i]);
        } catch (const std::bad_alloc& e) {
            std::cerr << "Memory allocation failed: " << e.what() << std::endl;
            destory();
        }
}

void MemoryPoolImpl::destory() {
    auto size = m_pools.size();
    for (size_t i = 0; i < size; i++) {
        m_pools[i]->~PoolTable();
    }
}

/*
    构建双端链表:
*/
void PoolTable::init_block() try {
    std::allocator<detail::MemoryBlock> memory_block_allocator;
    detail::MemoryBlock*                root = memory_block_allocator.allocate(1);
    std::construct_at(root, m_size, nullptr, nullptr);
    // available_list 节点本身作为root节点存有当前链表的大小信息
    size_t* cur_size = static_cast<size_t*>(available_list->data);
    *cur_size        = 0;
    available_list   = root;

    // 构建双端链表需要的头尾指针
    detail::MemoryBlock* head = root;
    detail::MemoryBlock* tail = root;
    // 设置 []-> <-[]
    for (size_t i = 0; i < m_available_size - 1; i++) {
        auto tmp_node = memory_block_allocator.allocate(1);
        std::construct_at(tmp_node, m_size, nullptr, nullptr, available_list);
        tail->next     = tmp_node;
        tmp_node->prev = tail;
        tail           = tmp_node;
        (*cur_size)++;
    }
    // 最后设置循环链表的头尾指针
    head->prev = tail;
    tail->next = head;

} catch (const std::bad_alloc&) {

    destory();  // 内存不够无法构建直接全部回退
}

/*
    内存池初始化检测:
*/
bool PoolTable::Check() const {
    MemoryBlock* check_next_ptr = available_list;
    MemoryBlock* check_prev_ptr = available_list;
    size_t       table_size     = 0;
    do {
        check_next_ptr = check_next_ptr->next;
        check_prev_ptr = check_prev_ptr->prev;
        table_size++;
        if (check_next_ptr == nullptr && check_prev_ptr == nullptr) {
            return false;
        }
    } while (check_next_ptr != check_prev_ptr);
    if (table_size != *static_cast<size_t*>(available_list->data)) {
        return false;
    }
    return true;
}

void PoolTable::destory() {
    auto availabl_begin = available_list->prev;
    while (available_list != availabl_begin) {
        availabl_begin = availabl_begin->prev;
        availabl_begin->next->~MemoryBlock();
    }
    auto assigned_begin = assigned_list->prev;
    while (assigned_list != assigned_begin) {
        assigned_begin = assigned_begin->prev;
        assigned_begin->next->~MemoryBlock();
    }
}
}  // namespace detail
}  // namespace ExCCCRender::Platform::MemoryPool
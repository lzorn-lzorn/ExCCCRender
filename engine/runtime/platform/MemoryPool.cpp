#include "../../runtime/platform/MemoyPool.hpp"

namespace ExCCCRender::Platform::MemoryPool {
namespace detail {
void MemoryPoolImpl::init_memory_pool() {
    block_size_table   = {16, 32, 64, 128, 256, 512, 1024, 2048, 4096};
    block_number_table = {512, 256, 128, 64, 16, 8, 8, 4, 2};
}

void MemoryPoolImpl::init_pool_table() {
    std::allocator<detail::PoolTable> pool_table_allocator;
    auto                              table_size = block_size_table.size();
    for (size_t i = 0; i < table_size; i++)
        try {
            pools[i] = pool_table_allocator.allocate(1);
            std::construct_at(pools[i], block_size_table[i], block_number_table[i]);
        } catch (const std::bad_alloc& e) {
            std::cerr << "Memory allocation failed: " << e.what() << std::endl;
            destory();
        }
}

void MemoryPoolImpl::destory() {
    auto size = pools.size();
    for (size_t i = 0; i < size; i++) {
        pools[i]->~PoolTable();
    }
}

/*
    构建双端链表
*/
void PoolTable::init_block() try {
    std::allocator<detail::MemoryBlock> memory_block_allocator;
    detail::MemoryBlock*                tail = memory_block_allocator.allocate(1);
    std::construct_at(tail, size, available_list, available_list);
    available_list->next = tail;
    available_list->prev = tail;
    for (size_t i = 0; i < available_size - 1; i++) {
        auto tmp_node = memory_block_allocator.allocate(1);
        std::construct_at(tmp_node, size, available_list, tail);
        available_list->prev = tmp_node;
        tail->next           = tmp_node;
        tail                 = tail->next;
    }
} catch (const std::bad_alloc& e) {

    destory();  // 内存不够无法构建直接全部回退
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
# recycled_ptr

可以进行垃圾回收的指针（需要指定gc root）。

垃圾回收使用最简单的标记回收法。对所有由recycled ptr分配的内存进行追踪。回收时由gc root出发遍历被追踪的内存块，并标记；然后释放所有被追踪但未被标记的内存块。

相较于shared_ptr，没有使用引用计数，所以memory overhead比较小。在时间性能上比较差，因为需要扫描内存。

// 单调队列/单调栈优化
// 在进行状态转移时，如果当前状态的所有值需要从上一个状态的某个连续的端中得到
// 即要对这个连续的段进行RMQ操作，此时可以使用单调队列/单调栈来维护
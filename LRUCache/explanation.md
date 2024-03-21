# Least-Recently-Used Cache

Problem statement [here](https://leetcode.com/problems/lru-cache/description/).

In order to efficiently compute which is the least recently used key when the cache's capacity is full we will mantain a queue that will store, in order, all the keys from least recently used to most recently used.
The main idea is to use the concept of a linked list but in python and without the use of pointers.
In that sense, each key will store which is the key right before and right after them in the queue.
We will use -1 as a representation of a "null pointer".


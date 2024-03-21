# problem statement: https://leetcode.com/problems/lru-cache/description/

'''
Explanation:
In order to efficiently compute which is the least recently used key when the cache's capacity is full we will mantain a queue that 
will store, in order, all the keys from least recently used to most recently used. The main idea is to use the concept of a linked list
but in python and without the use of pointers. In that sense, each key will store which is the key right before and right after them in
the queue. We will use -1 as a representation of a "null pointer".
'''

class LRUCache(object):

    def __init__(self, capacity):
        self.max_cap = capacity
        self.cur_cap  = 0 # This will count the number of keys used
        self.dict = {-1: -1} # This dictionary will store all the current key-value pairs available in the cache
        self.time = 0
        # These 4 variables will encode the state of the queue at all moment.
        # prev[k] and next[k] will store the previous and the next key of "k" in the queue  
        self.prev = {-1: -1}
        self.next = {-1: -1}
        # beg_queue and end_queue will store the first key and the last key of the queue
        self.beg_queue = -1
        self.end_queue = -1

    def update(self, key): # This method will be called whenever a key is used and it will update the key's position in the queue
        self.time += 1
        if key == self.end_queue:
            return
        if key in self.dict.keys():
            p = self.prev[key]
            n = self.next[key]
            self.next[p] = n
            self.prev[n] = p
        if self.beg_queue == key:
            self.beg_queue = self.next[key]
        self.next[self.end_queue] = key
        self.prev[key] = self.end_queue
        self.next[key] = -1
        self.end_queue = key
        if self.beg_queue == -1:
            self.beg_queue = key
        
    def log_status(self):    
        print("--------TIME:", self.time)
        print("max_cap", self.max_cap)
        print("cur_cap", self.cur_cap)
        print("dict", self.dict)
        print("prev", self.prev)
        print("next", self.next)
        print("beg_queue", self.beg_queue)
        print("end_queue", self.end_queue)
        print("=====================================")
   

    def get(self, key):
        if not key in self.dict.keys():
            return -1
        self.update(key)
        return self.dict[key]
        

    def put(self, key, value):
        self.update(key)
        if key in self.dict.keys():
            self.dict[key] = value
            return
        self.dict[key] = value
        if self.cur_cap < self.max_cap:
            self.cur_cap += 1
            return
        lru = self.beg_queue
        self.beg_queue = self.next[lru]
        self.dict.pop(lru)
        

answers = []
lruc = LRUCache(2)
answers.append(None)
answers.append(lruc.put(1,1))
answers.append(lruc.put(2,2))
answers.append(lruc.get(1))
answers.append(lruc.put(3,3))
answers.append(lruc.get(2))
answers.append(lruc.put(4,4))
answers.append(lruc.get(1))
answers.append(lruc.get(3))
answers.append(lruc.get(4))

assert(answers == [None, None, None, 1, None, -1, None, -1, 3, 4])

answers = []
lruc = LRUCache(2)
answers.append(None)
answers.append(lruc.put(2,1))
answers.append(lruc.put(3,2))
answers.append(lruc.get(3))
answers.append(lruc.get(2))
answers.append(lruc.put(4,3))
answers.append(lruc.get(2))
answers.append(lruc.get(3))
answers.append(lruc.get(4))

assert(answers == [None, None, None, 2, 1, None, 1, -1, 3])

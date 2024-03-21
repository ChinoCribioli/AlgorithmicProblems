# Context

This is my resolution to an algorithmic problem called Lowest Common Parent, which I had to solve in the context of an interview process. The problem setup consists of a tree and the task is to, given two nodes in the tree, efficiently compute their first common ancestor. This solution was implemented in C++ and took less than 2 hours.

# Challenge - FindParent

We are building a command line tool to navigate the file system. We want to add a command that given two file paths, can find the first parent folder that contains both paths.

So for example: 

```jsx

findParent "a/b/c" "a/b/d"
-> "/a/b"
```

Because filesystems might have aliases, we cannot use the file path to find the parent folder at a glance. (i.e. /var might be pointing to /a/b). We need to find the parent folder by navigating the filesystem.

**Challenge**

Given an input that represents a filesystem, and two files, find the closest folder that contains both file paths.

### **Boilerplate**

```jsx
function findParent() {
  //implement this function
}

class File {
	constructor(name) {
    this.children = [];
    this.name = name;
  }

  addChild(file) {
    this.children.push(file)
  }
}

/*
Example input

root ->
  a ->
    c
    d
  b    
*/

const root = new File('root')
const [a,b,c,d] = ['abcd'].split('').map(char => new File(char))      

root.addChild(a)
root.addChild(b)
a.addChild(c)
a.addChild(d)

findParent(root, a, b)
//-> root

findParent(root, c, d)
//-> a

```

**We expect you to:**

1. Provide an elegant and performant implementation of this function
2. An explanation of the algorithm used and a correct implementation

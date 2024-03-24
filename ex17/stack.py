class Stack:
    def __init__(self):
        self.items = []

    def is_empty(self):
        return len(self.items) == 0

    def push(self, item):
        self.items.append(item)

    def pop(self):
        if not self.is_empty():
            return self.items.pop()
        else:
            raise IndexError("pop from empty stack")

    def peek(self):
        if not self.is_empty():
            return self.items[-1]
        else:
            raise IndexError("peek from empty stack")
    
    def size(self):
        return len(self.items)

# Example usage
stack = Stack()
stack.push(13)
stack.push(43)
stack.push(53)

print("Stack size:", stack.size()) # output: 3
print("Top element:", stack.peek()) # output: 53

print("Popped element", stack.pop()) # output: 53
print("Popped element", stack.pop()) # output: 43

print("Is stack empty", stack.is_empty()) # output: False

print("Popped element", stack.pop()) # output: 13
print("Is stack empty", stack.is_empty()) # output: True

    
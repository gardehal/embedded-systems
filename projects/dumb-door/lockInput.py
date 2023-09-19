
class LockInput:
    
    action: int
    steps: int
    source: int
    caller: int
    
    def __init__(self, action: int, steps: int, source: str, caller: str):
        self.action = action
        self.steps = steps
        self.source = source
        self.caller = caller

class LockInput:
    
    action: int
    source: str
    caller: str
    steps: int
    stepSleepMs: int
    
    def __init__(self, action: int, source: str, caller: str, steps: int, stepSleepMs: int):
        self.action = action
        self.source = source
        self.caller = caller
        self.steps = steps
        self.stepSleepMs = stepSleepMs
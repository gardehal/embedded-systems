
class RgbColor:
    off = (0, 0, 0)
    white = (255, 255, 255)
    red = (255, 0, 0)
    green = (0, 255, 0)
    blue = (0, 0, 255)
    orange = (255, 128, 0)
    yellow = (255, 255, 0)
    lime = (128, 255, 0)
    mint = (0, 255, 128)
    teal = (0, 255, 255)
    navyBlue = (0, 128, 255)
    purple = (128, 0, 255)
    magenta = (255, 0, 255)
    pink = (255, 0, 128)
    
    all = [off,
           white,
           red,
           green,
           blue,
           orange,
           yellow,
           lime,
           mint,
           teal,
           navyBlue,
           purple,
           magenta,
           pink,]
    
    def dimmed(self, color: tuple, multiplier: float) -> tuple:
        # Returned a tuple of given color, with values multiplied with given multiplier (0 to 1), e.g. c.dimmed(c.blue, 0.5)
        
        return (color[0] * multiplier, color[1] * multiplier, color[2] * multiplier)

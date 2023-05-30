# Imports
# ---------------------------
import numpy as np
from classes import *

# Parameters
# ---------------------------

# used to make animation
MP4 = True
# speed of birds
SPEED = 0.01
# bird size
SIZE = 0.04
# COLOR
COLOR = (200,206,209)
# WHITE
WHITE = (255,255,255)
# BLACK
BLACK = (0,0,0)
# RED
RED = (255, 0, 0)
# LIFETIME
LIFETIME=360
# FIELD
FIELD = 1
# size of screen
screen_size = [800, 800]
# Star positions
note_positions = star_positions()
# dictionnary of indices for notes
note_index = {i:(i+6)%12 for i in range(1,13)}
# color palette
note_palette = {
    1:WHITE,
    2:WHITE,
    3:WHITE,
    4:WHITE,
    5:WHITE,
    6:WHITE,
    7:WHITE,
    8:WHITE,
    9:WHITE,
    10:WHITE,
    11:WHITE,
    12:WHITE,
}
# params dictionnary
params = {'speed':SPEED,
            'size':SIZE,
            'color':COLOR,
            'field':FIELD}
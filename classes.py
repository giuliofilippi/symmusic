# Imports
# ---------------------------
import numpy as np

# Functions
# ---------------------------

# Positions of the 12 notes
def star_positions():
    notes = [1,2,3,4,5,6,7,8,9,10,11,12]
    angles = [2*np.pi*(i-5)/12+np.pi/12 for i in notes]
    positions = [np.array([np.cos(ang), np.sin(ang)]) for ang in angles]
    return positions

# Normalize a vector
def normalize(v):
    v = np.array(v)
    norm = np.linalg.norm(v)
    if norm == 0: 
       return v
    return v / norm

# Position transform
def vector_transform(x, loc, scale):
    return np.array(x)*scale + loc

# distance between objs
def distance(obj1, obj2):
    dx = (obj1.pos-obj2.pos)[0]
    dy = (obj1.pos-obj2.pos)[1]
    return np.linalg.norm(np.array([dx,dy]))

# Get the points of triangle based on position and velocity vector
def get_triangle_points(pos, direction, size, loc, scale):
    normal = np.array([direction[1],-direction[0]])
    loc = np.array(loc)
    x1 = (pos + direction * size)*scale+loc
    x2 = (pos - normal * size/4)*scale+loc
    x3 = (pos + normal * size/4)*scale+loc
    return [x1,x2,x3]

# Star positions
note_positions = star_positions()

# dictionnary of indices for notes
note_index = {i:(i+6)%12 for i in range(1,13)}

def compute_hit(pos, dir, obj_size):
    for i in range(1,13):
        x = note_positions[note_index[i]]
        if np.linalg.norm(pos+obj_size*dir-x)<=15/350:
            return i
    return -1


# Classes
# ---------------------------

# Class to generate objs
class Obj:
    # Initialise Object
    def __init__(self, pos, dir, speed, size, color, field):
        self.pos = np.array(pos)
        self.speed = speed
        self.velocity = speed * normalize(np.array(dir))
        self.size = size
        self.color = color
        self.field = field
        self.time = 0
        self.hitnote = -1
        self.note = -1

    # Direction from velocity
    def direction(self):
        vec = np.array([self.velocity[0],self.velocity[1]])
        vel = np.linalg.norm(vec)
        return vec/vel

    # Neighbours of a obj
    def neighbours(self, list_of_objs):
        neighbours = []
        for brd in list_of_objs:
            if distance(self,brd)<self.field and brd!=self:
                neighbours.append(brd)
        return neighbours

    # Cohesion: we change a objs velocity based on neighbouring objs center of mass
    def cohesion_update(self, neighbours, gamma=0.0004):
        N = len(neighbours)
        if N==0:
            com = self.pos
        else:
            com = sum([x.pos for x in neighbours])/N
        delta_v = normalize(com - self.pos)*gamma
        self.velocity += delta_v
        return self

    # Separation : nearby objs repel each other
    def separation_update(self, neighbours, gamma=0.0001):
        delta_v = np.array([0,0])
        for obj in neighbours:
            if distance(self,obj)<2*self.size:
                delta_v = delta_v + normalize(self.pos - obj.pos)*gamma
        self.velocity += delta_v
        return self
        
    # Gravity : objs gravitational attraction to origin
    def gravitational_update(self, gamma=0.00013):
        origin = np.array([0,0])
        delta_v = normalize(origin - self.pos)*gamma
        self.velocity += delta_v
        return self

    # Acceleration / Deceleration
    def acceleration_update(self):
        current_speed = np.linalg.norm(self.velocity)
        self.velocity += (self.velocity/current_speed)*(self.speed - current_speed)/10
        return self

    def bound_update(self):
        R = np.linalg.norm(self.pos)
        if R>=1 and self.time>20:
            self.time = 360
        return self

    def hit_update(self):
        R = np.linalg.norm(self.pos)
        if R>=1-15/350 and self.time>10:
            self.hitnote = compute_hit(self.pos,self.direction(),self.size)
            if self.hitnote!=-1:
                self.time = 360
        return self
        
    # Final update changing all parameters
    def update(self, list_of_objs):

        # Find neighbours of obj
        neighbours = self.neighbours(list_of_objs)

        # Gravitational Update
        #self.gravitational_update()

        # Cohesion Update
        self.cohesion_update(neighbours)

        # Separation Update
        self.separation_update(neighbours)

        # Acceleration Updates
        self.acceleration_update()

        # Position Updates
        self.pos = self.pos + self.velocity

        # Hit Update
        self.hit_update()

        # Out of bounds Update
        self.bound_update()

        # Time update
        self.time += 1

        return self
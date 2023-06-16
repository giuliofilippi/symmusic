# Imports
# ---------------------------
import numpy as np
import pygame
import rtmidi
from classes import *
from params import *


# Pygame
# ---------------------------
def main():
    """
    This is our main program.
    """
    pygame.init()
    # Mido
    midiout = rtmidi.MidiOut()
    midiout.open_virtual_port('foo')
    #port = mido.open_output(name='foo', virtual=True)
    # Set the height and width of the screen
    screen = pygame.display.set_mode(screen_size)
    # Caption
    pygame.display.set_caption("Visualization")
    # Loop until the user clicks the close button.
    done = False
    # Used to manage how fast the screen updates
    clock = pygame.time.Clock()
    # obj list
    obj_list = []
    # color of note circles
    note_colors = note_palette.copy()

    # -------- Main Program Loop -----------
    count = 0
    while not done:
        count+=1

        # --- Animation
        if MP4 == True:
            filename = 'animation/'+'capture_'+str(count)+'.jpeg'
            pygame.image.save(screen, filename)

        # --- Events
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                done = True

            # Keydown - for notes
            if event.type == pygame.KEYDOWN:
                for i in range(1,10):
                    if event.unicode == str(i):
                        pos = note_positions[note_index[i]]
                        dir = note_positions[(note_index[i]+7)%12]-note_positions[note_index[i]]
                        new_obj = Obj(pos=pos, dir=dir, **params)
                        new_obj.note = 60+i-1
                        obj_list.append(new_obj)
                        # music
                        note_on = [0x90, new_obj.note, 112]
                        midiout.send_message(note_on)

                if event.unicode == '0':
                    pos = note_positions[note_index[10]]
                    dir = note_positions[(note_index[10]+7)%12]-note_positions[note_index[10]]
                    new_obj = Obj(pos=pos, dir=dir, **params)
                    obj_list.append(new_obj)
                    new_obj.note = 70
                    # music
                    note_on = [0x90, new_obj.note, 112]
                    midiout.send_message(note_on)

                if event.unicode == '-':
                    pos = note_positions[note_index[11]]
                    dir = note_positions[(note_index[11]+7)%12]-note_positions[note_index[11]]
                    new_obj = Obj(pos=pos, dir=dir, **params)
                    obj_list.append(new_obj)
                    new_obj.note = 71
                    # music
                    note_on = [0x90, new_obj.note, 112]
                    midiout.send_message(note_on)

                if event.unicode == '=':
                    pos = note_positions[note_index[12]]
                    dir = note_positions[(note_index[12]+7)%12]-note_positions[note_index[12]]
                    new_obj = Obj(pos=pos, dir=dir, **params)
                    obj_list.append(new_obj)
                    new_obj.note = 72
                    # music
                    note_on = [0x90, new_obj.note, 112]
                    midiout.send_message(note_on)
                    
                if event.unicode == ' ':
                    obj_list = []
                    for n in range(21,109):
                        note_off = [0x90, n, 0]
                        midiout.send_message(note_off)


        # --- Logic
        for obj in obj_list:
            # Update obj parameters
            obj.update(obj_list)

            # remove older objs
            if obj.time > LIFETIME:
                obj_list.remove(obj)
                # music
                note_off = [0x90, obj.note, 0]
                midiout.send_message(note_off)

            # new objs
            if obj.hitnote != -1:
                pos = note_positions[note_index[obj.hitnote]]
                dir = note_positions[(note_index[obj.hitnote]+7)%12]-pos
                new_obj = Obj(pos=pos, dir=dir, **params)
                obj_list.append(new_obj)
                new_obj.note = 60 + obj.hitnote - 1
                note_colors[obj.hitnote]=(0,255,0)
                # music
                note_on = [0x90, new_obj.note, 112]
                midiout.send_message(note_on)

        # --- Drawing the Background
        screen.fill((0,0,0))

        # --- Drawing the Star Pattern
        for i in range(1,13):
            pos = vector_transform(note_positions[note_index[i]], loc=400, scale=350)
            pygame.draw.circle(screen, color=note_colors[i], center=pos, radius=15)
            font = pygame.font.SysFont(None, 24)
            img = font.render(str(i), True,BLACK)
            screen.blit(img, pos-np.array([8,8]))
            
        # --- Drawing the objs
        for obj in obj_list:
            points = get_triangle_points(obj.pos,obj.direction(),obj.size, loc=[400,400], scale=350)
            pygame.draw.polygon(screen, obj.color, points)

        # --- Reset some params
        note_colors = note_palette.copy()

        # --- Wrap-up (Limit to 60 frames per second)
        clock.tick(30)

        # --- Update screen
        pygame.display.flip()

    # Close everything down
    pygame.quit()

if __name__ == "__main__":
    main()



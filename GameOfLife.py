import pygame as pg
import numpy as np
import time
import numba as nb

class Life:
    """
    The game of life
    """
    def __init__(self, ROWS, COLUMNS):
        self.ROWS = ROWS
        self.COLUMNS = COLUMNS
        self.grid = np.zeros((self.COLUMNS, self.ROWS))
    
    def __str__(self):
        return str(self.grid)

    

    def nextGeneration(self):
        """
        Generates a new generation from the current one given the standard game rules.
        """
        newGrid = np.zeros((self.COLUMNS, self.ROWS))
        nextGenerationCalculation(self.grid, newGrid)

        self.grid = newGrid

    def randomize(self):
        """
        Creates a random grid.
        """
        self.grid = np.random.randint(0,2,(self.COLUMNS, self.ROWS))
@nb.njit
def nextGenerationCalculation(oldGrid, newGrid):
    for y in range(oldGrid.shape[0]):
        for x in range(oldGrid.shape[1]):
            count = countNeighbours(oldGrid, x,y)
            if oldGrid[y][x]==1:
                if count==2 or count == 3:
                    newGrid[y][x] = 1
            else: #dead but can come alive
                if count ==3:
                    newGrid[y][x] = 1
@nb.njit                   
def countNeighbours(grid, x, y):
    """
    Counts the neighbours around the given cell.
    If the cell is on the edge, only the neighbours on the grid will be counted.
    """
    count = 0
    for dx in range(x-1, (x+1)+1):
        dx %= grid.shape[0] #To connect edges instead of clipping

        for dy in range(y-1, (y+1)+1):
            dy %= grid.shape[1] #To connect top and bottom
            if dx == x and dy == y: continue

            count += grid[dy][dx]
    return count


if __name__ == "__main__":
    import os
    #Always center the game window
    os.environ['SDL_VIDEO_CENTERED'] = '1'
    
    WIN_SIZE = 1000
    ROWS = 200
    COLUMNS = 200
    squareSide = WIN_SIZE/ROWS
    life = Life(ROWS, COLUMNS)
    life.randomize()

    pg.init()
    pg.font.init()
    font = pg.font.SysFont('Comic Sans MS', 30)
    
    timer = pg.time.Clock() #Time control with pygame

    display: pg.display = pg.display.set_mode((WIN_SIZE, WIN_SIZE))
    
    running = True
    
    while running:
        display.fill((0, 0, 0))
        for event in pg.event.get([pg.QUIT,]): #Limit events to only QUIT event
            print('Ending Simulation...')
            if event.type == pg.QUIT:
                running = False
                
        game_surf = pg.surfarray.make_surface(life.grid) #Create surface from array
        game_surf = pg.transform.scale(game_surf, (WIN_SIZE, WIN_SIZE)) #Scale surface to display
        display.blit(game_surf, (0, 0)) #Show surface
        
        text = font.render(f"FPS: {round(timer.get_fps())}",True, (255,255,255))
        display.blit(text, (0,0))
        
        pg.display.flip()
        life.nextGeneration()
        
        timer.tick(60) #Limit to 60 FPS
    pg.quit()




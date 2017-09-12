import os
import time
##### YOU MUST HAVE YOUTUBE-DL INSTALLED! ####

urls = {
    'battle' : 'https://www.youtube.com/watch?v=lf7qedGXOZg',
    'scenario theme(zeal)' : 'https://www.youtube.com/watch?v=Swsswovrlgw'
}


print("Installing songs...")
time.sleep(.5)

os.system("youtube-dl -x '%s' --audio-format'

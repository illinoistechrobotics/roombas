# These are the required libraries (make sure they are installed)
import pygame    # for controller support
import time      #for, well, time
import bluetooth # needed for bluetooth communication
 
bluetooth_addr = "xx:xx:xx:xx:xx:xx" # The MAC address of the ESP32
bluetooth_port = 1 # Channel 1 for RFCOMM
bluetoothSocket = bluetooth.BluetoothSocket (bluetooth.RFCOMM) # Create a BT socket
bluetoothSocket.connect((bluetooth_addr,bluetooth_port))       # Use created socket to connect to ESP

# Start pygame to initialize joystick input
pygame.init()
pygame.joystick.init() 
joysticks = [pygame.joystick.Joystick(x) for x in range(pygame.joystick.get_count())] #pygame will find any number of joysticks present on your computer

#Some variables
done = False    # Used to kill the controls polling routine, tie it to one of the buttons to kill this script
Xaxis = 0
Yaxis = 0
button = []

for i in range(12):#create an array to put button values in
    button.append(0)


while done==False:
    for event in pygame.event.get(): #whenever we quit pygame pygame will end
        if event.type == pygame.QUIT:
            done=True

    # Getting button input and sending it over
    joystick = pygame.joystick.Joystick(0)
    joystick.init()
    buttonPacket = 0
    for j in range(8): #send the first few values of buttons (adding more and decreasing the delay on sending packets seems to make recieved packets less accurate)
        buttonPacket = (buttonPacket<<1)+joystick.get_button(j)     #Append the true/false bit of the button state onto the button number.
       
       
    bluetoothSocket.send(str(buttonPacket)+"\t")    # Now we will send the button packet over to the ESP
    print(buttonPacket)
        
    Xaxis = int(round(joystick.get_axis(0) * 15 + 15))      # This is polling for X and Y axes.  The last joystick found is the primary
    Yaxis = int(round(30-(joystick.get_axis(3)* 15 + 15)))  # Here we just invert the output of the right Y axis backward 

    #The joystick axis are indexed at 0, so Left X = 0, Left Y = 1, Right X = 2, Right Y = 3 and so on if you have more

    print("X axis = " + str(Xaxis) + " Y axis = " + str(Yaxis)) # Debug output

    packet = [Xaxis, Yaxis + ( 1 << 5)] 
    bluetoothSocket.send(str(Xaxis)+'\t'+str(Yaxis)+'\n')   # Now we will send the X and Y axis packet over to the ESP
        
    time.sleep(.05) # Wait so that ESP-32 is not overwhelmed with packets 


bluetoothSocket.close()	
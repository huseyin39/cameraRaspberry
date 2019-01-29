import RPi.GPIO as GPIO
import time
import socket

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
GPIO.setup(17, GPIO.OUT)


pwm=GPIO.PWM(17,100)
pwm.start(0)


port = 20000

def setServer():
    connexion_serveur = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    connexion_serveur.bind(('', port))
    connexion_serveur.listen(5)
    print("Le serveur ecoute sur le port {}".format(port))

    connexion_client, infos_connexion = connexion_serveur.accept()
    print("Connected")
    
    connexion_client.send(b"test\n")

    
    while (True):
        msg_recu = connexion_client.recv(1024)
        print(msg_recu)

        messageToClient = b""

        if(check_int(msg_recu) == True):
           if(int(msg_recu) >= 0 and int(msg_recu) <= 180):
                setAngle(int(msg_recu))
           else:
                print("ca marche plus ")
        elif(msg_recu == 'end'):
            
            messageToClient = b"la fermeture de serveur"
            connexion_client.close()
            setServer()
        else:
           messageToClient = b"You must give an integer between 0 and 180"
             
        connexion_client.send(b"You must give an integer between 0 and 180")
        


def setAngle(angle):
    angleChoisi = angle/10 + 2.5
    pwm.ChangeDutyCycle(angleChoisi)
    time.sleep(0.5)



def check_int(s):
    if s[0] in ('-', '+'):
        return s[1:].isdigit()
    return s.isdigit()


if __name__ == "__main__":
    setServer()
    

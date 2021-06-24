import serial
import cv2


ser = serial.Serial("COM3", "9600")

# подгружаем каскады
face_cascades = cv2.CascadeClassifier(cv2.data.haarcascades + "haarcascade_frontalface_default.xml")

cap = cv2.VideoCapture(0)

while True:
    success, img = cap.read()

    img = cv2.flip(img, 1)
    img_gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

    faces = face_cascades.detectMultiScale(img_gray, 1.1, 19)
    for (x,y,w,h) in faces:
        cv2.rectangle(img, (x,y),(x+w,y+h), (0,255,0),2)

        # передаем центр лица
        xx = int(x+w/2)
        yy = int(y+h/2)
        data = f"X{xx}Y{yy}"
        print(data)
        ser.write(data.encode("utf-8"))
    cv2.imshow('rez', img)
    if cv2.waitKey(1) & 0xff == ord("q"):
        break


cap.release()
cv2.destroyAllWindows()
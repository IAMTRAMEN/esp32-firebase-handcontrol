import firebase_admin
from firebase_admin import credentials
from firebase_admin import db
import cv2
import cvzone
from cvzone.HandTrackingModule import HandDetector



# Fetch the service account key JSON file contents
cred = credentials.Certificate("ss.json")
# Initialize the app with a service account, granting admin privileges
firebase_admin.initialize_app(
    cred, {"databaseURL": "DATABASEURL"}
)

# Save data
ref = db.reference("/")
print('✔ Connected to Firebase !')

cap = cv2.VideoCapture(0)
detector = HandDetector(maxHands=1)
while True:
    ledy = db.reference("/led/status").get()
    
    success, img = cap.read()
    hands, img = detector.findHands(img)
    x =int(ledy)
    if hands:
        hand = hands[0]
        fingers = detector.fingersUp(hand)
        # fingers == [0, 1, 0, 0, 0]:
        if all(finger == 1 for finger in fingers):
            ref.set(
                {
                    "led": {
                        "status": "1",
                    }
                }
            )

        elif x==0 or fingers == [0, 0, 0, 0, 0] :
            ref.set(
                {
                    "led": {
                        "status": "0",
                    }
                }
            )
        
    print(x)
    cv2.imshow("OUT", img)
    if cv2.waitKey(1) == ord("q"):
        break

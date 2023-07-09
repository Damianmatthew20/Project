import time
from win10toast import ToastNotifier
import datetime


def getTime():
    hour = int(input("Hour of interval: "))
    minute = int(input("Minute of interval: "))
    second = int(input("Second of interval: "))
    time_interval = (second * (minute * 60) * (hour * 3600))
    return time_interval

def log():
    now = datetime.datetime.now()
    start_time = now.strftime("%H:%M:%S")

    with open("log.txt", 'a') as f:
        f.write(f"You drank water {now}\n")
    
    return 0

def notify():
    notification = ToastNotifier()
    notification.show_toast("Time to drink water!")
    log()
    return 0

def startTime(time_interval):
    while True:
        time.sleep(time_interval)
        notify()

if __name__ == "__main__":
    time_interval = getTime()
    startTime(time_interval)
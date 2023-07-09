import pyqrcode
import png
from pyqrcode import QRCode

web_convert = input("Enter your url: ")
url = pyqrcode.create(web_convert)
url.svg("QR_DB.svg", scale = 8)
url.png("QR_DB.png", scale = 8)
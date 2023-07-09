import tkinter
from tkinter.constants import END


# Setup
root = tkinter.Tk()
root.title("Kalkulator")
root.geometry("395x330")
screen = tkinter.Entry(root, width = 40, borderwidth = 5)
screen.grid(column = 0, row = 0, columnspan = 6, padx = 10, pady = 10)


# Tombol
angka_0 = tkinter.Button(root, text = "0", padx = 109, pady= 20, command = lambda:angka(0))
angka_1 = tkinter.Button(root, text = "1", padx = 30, pady= 20, command = lambda:angka(1))
angka_2 = tkinter.Button(root, text = "2", padx = 30, pady= 20, command = lambda:angka(2))
angka_3 = tkinter.Button(root, text = "3", padx = 30, pady= 20, command = lambda:angka(3))
angka_4 = tkinter.Button(root, text = "4", padx = 30, pady= 20, command = lambda:angka(4))
angka_5 = tkinter.Button(root, text = "5", padx = 30, pady= 20, command = lambda:angka(5))
angka_6 = tkinter.Button(root, text = "6", padx = 30, pady= 20, command = lambda:angka(6))
angka_7 = tkinter.Button(root, text = "7", padx = 30, pady= 20, command = lambda:angka(7))
angka_8 = tkinter.Button(root, text = "8", padx = 30, pady= 20, command = lambda:angka(8))
angka_9 = tkinter.Button(root, text = "9", padx = 30, pady= 20, command = lambda:angka(9))
hapus = tkinter.Button(root, text = "clear", padx = 60, pady= 20, command = lambda:op_hapus())
tambah = tkinter.Button(root, text = "+", padx = 29, pady= 20, command = lambda:op_tambah())
kurang = tkinter.Button(root, text = "-", padx = 30, pady= 20, command = lambda:op_kurang())
kali = tkinter.Button(root, text = "x", padx = 29, pady= 20, command = lambda:op_kali())
bagi = tkinter.Button(root, text = "/", padx = 30, pady= 20, command = lambda:op_bagi())
sama_dengan = tkinter.Button(root, text = "=", padx = 68, pady= 20, command = lambda:op_sama_dengan())

angka_0.grid(row = 4, column = 0, columnspan = 3, padx = 2, pady = 1)
angka_1.grid(row = 3, column = 0, padx = 2, pady = 1)
angka_2.grid(row = 3, column = 1, padx = 2, pady = 1)
angka_3.grid(row = 3, column = 2, padx = 2, pady = 1)
angka_4.grid(row = 2, column = 0, padx = 2, pady = 1)
angka_5.grid(row = 2, column = 1, padx = 2, pady = 1)
angka_6.grid(row = 2, column = 2, padx = 2, pady = 1)
angka_7.grid(row = 1, column = 0, padx = 2, pady = 1)
angka_8.grid(row = 1, column = 1, padx = 2, pady = 1)
angka_9.grid(row = 1, column = 2, padx = 2, pady = 1)
hapus.grid(row = 1, column = 4, columnspan = 2, padx = 2, pady = 1)
tambah.grid(row = 2, column = 4, padx = 2, pady = 1)
kurang.grid(row = 3, column = 4, padx = 2, pady = 1)
kali.grid(row = 2, column = 5, padx = 2, pady = 1)
bagi.grid(row = 3, column = 5, padx = 2, pady = 1)
sama_dengan.grid(row = 4, column = 4, columnspan = 2, padx = 2, pady = 1)


# Fungsi
def angka(nilai) :
    angka = screen.get()
    screen.delete(0, END)
    screen.insert(0, str(angka) + str(nilai))

def op_tambah() :
    angka_awal = screen.get()
    global angka_pertama
    global operasi
    operasi = "penjumlahan"
    angka_pertama = int(angka_awal)
    screen.delete(0, END)

def op_kurang() :
    angka_awal = screen.get()
    global angka_pertama
    global operasi
    operasi = "pengurangan"
    angka_pertama = int(angka_awal)
    screen.delete(0, END)

def op_kali() :
    angka_awal = screen.get()
    global angka_pertama
    global operasi
    operasi = "perkalian"
    angka_pertama = int(angka_awal)
    screen.delete(0, END)

def op_bagi() :
    angka_awal = screen.get()
    global angka_pertama
    global operasi
    operasi = "pembagian"
    angka_pertama = int(angka_awal)
    screen.delete(0, END)

def op_hapus() :
    screen.delete(0, END)

def op_sama_dengan() :
    angka_akhir = screen.get()
    screen.delete(0, END)
    angka_kedua = int(angka_akhir)

    if operasi == "penjumlahan" :
        screen.insert(0, angka_pertama + angka_kedua)

    elif operasi == "pengurangan" :
        screen.insert(0, angka_pertama - angka_kedua)

    elif operasi == "perkalian" :
        screen.insert(0, angka_pertama * angka_kedua)

    elif operasi == "pembagian" :
        screen.insert(0, angka_pertama / angka_kedua)


root.mainloop()
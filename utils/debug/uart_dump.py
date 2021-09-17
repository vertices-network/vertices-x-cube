#!/usr/bin/env python
import getopt
from serial import Serial
import sys
from threading import Thread


def user_input(ser):
    print("🧑‍💻 You can type commands")
    while 1:
        c = input()
        try:
            ser.write(c.encode('utf-8'))
            ser.write('\n'.encode('utf-8'))
        except Exception as err:
            print(err)


def main(argv):
    baud_rate = 115200
    port = ""
    help = "Usage: {} -p <port> [-b <baud_rate>] \nDefault baud rate: 115200".format(
        sys.argv[0])

    if len(sys.argv) < 2:
        print(help)
        quit()

    try:
        opts, args = getopt.getopt(argv[1:], "p:b:h", ["port="])

        if opts != None:
            for opt, arg in opts:
                if opt == '-h':
                    print(help)
                    sys.exit()
                elif opt in ("-p", "--port"):
                    port = arg
                elif opt in "-b":
                    baud_rate = int(arg)
    except getopt.GetoptError:
        print(help)

    ser = Serial(port, 115200)
    print("🎧 Listening UART (8N1 {}) on {}".format(baud_rate, port))

    Thread(target=user_input, args=[ser]).start()

    while 1:
        line = ser.readline()
        if not line:
            break

        to_print = ""
        try:
            to_print = line.decode('utf-8').rstrip()
        except Exception as err:
            print("ERROR: {}".format(err))

        print(to_print)


if __name__ == '__main__':
    main(sys.argv)

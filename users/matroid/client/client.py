import hid
import easydict
import sys
import IPython
from datetime import datetime
from PyQt5 import QtCore, QtGui, QtWidgets
if sys.platform == 'darwin':
    import pync


if sys.platform not in ['darwin']:
    print('%s is not a supported OS.' % sys.platform)


def log(k, m):
    print(datetime.now().strftime("%Y %m %d %H:%M:%S"), k.name, m)


def notify(k, m):
    if sys.platform == 'darwin':
        pync.notify(m)
    log(k, m)


keyboards = [
    easydict.EasyDict(
        name='Matrix Noah',
        vendor_id=0x4D58,
        product_id=0x0065,
        interface=None,
        in_queue=[],
        in_queue_mutex=QtCore.QMutex(),
        out_queue=[],
        out_queue_mutex=QtCore.QMutex()
    )
]


def review():
    for i, k in enumerate(keyboards):
        log(k, 'start review')
        if k.interface:
            with QtCore.QMutexLocker(k.in_queue_mutex):
                while True:
                    j = [j for j, m in enumerate(k.in_queue) if m.name == 'heartbeat']
                    if not j:
                        notify(k, '%s is lost.' % k.name)
                        k.interface.close()
                        k.interface = None
                        break
                    j = j[0]
                    m = k.in_queue[j]
                    k.in_queue.pop(j)
                    if int(m.content) == k.heartbeat:
                        break
        else:
            for j in range(16):
                try:
                    d = hid.device()
                    d.open(k.vendor_id, k.product_id)
                    d.set_nonblocking(1)
                    k.interface = d
                    k.heartbeat = 0
                    notify(k, '%s is detected.' % k.name)
                    break
                except:
                    pass
        if k.interface:
            k.heartbeat += 1
            with QtCore.QMutexLocker(k.out_queue_mutex):
                k.out_queue.append(easydict.EasyDict(name='heartbeat', content=k.heartbeat))
        log(k, 'end review')


app = QtWidgets.QApplication(sys.argv)
app.setQuitOnLastWindowClosed(False)


review_timer = QtCore.QTimer()
review_timer.timeout.connect(review)
review_timer.start(1000)


def send_messages():
    for i, k in enumerate(keyboards):
        log(k, 'start send_messages')
        with QtCore.QMutexLocker(k.out_queue_mutex):
            if k.interface:
                for m in k.out_queue:
                    m = m.name + ' ' + str(m.content)
                    log(k, 'send' + ' ' + m)
                    m = [ord(c)for c in m]
                    m = m + [0] * (32 - len(m))
                    k.interface.write(m)
            k.out_queue = []
        log(k, 'end send_messages')


send_messages_timer = QtCore.QTimer()
send_messages_timer.timeout.connect(send_messages)
send_messages_timer.start(100)


def receive_messages():
    for i, k in enumerate(keyboards):
        log(k, 'start receive_messages')
        with QtCore.QMutexLocker(k.in_queue_mutex):
            if k.interface:
                while True:
                    try:
                        m = k.interface.read(32)
                    except:
                        m = []
                    if not m:
                        break
                    while m and m[-1] == 0:
                        m.pop(-1)
                    if m:
                        m = ''.join([chr(c)for c in m])
                        log(k, 'receive' + ' ' + m)
                        m = m.split(maxsplit=1)
                        k.in_queue.append(easydict.EasyDict(name=m[0], content=m[1]))
        log(k, 'end receive_messages')


receive_messages_timer = QtCore.QTimer()
receive_messages_timer.timeout.connect(receive_messages)
receive_messages_timer.start(100)


app.exec_()

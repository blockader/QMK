import hid
import easydict
import sys
import IPython
from PyQt5 import QtCore, QtGui, QtWidgets
if sys.platform == 'darwin':
    import pync


if sys.platform not in ['darwin']:
    print('%s is not a supported OS.' % sys.platform)


def notify(m):
    if sys.platform == 'darwin':
        pync.notify(m)


keyboards = [easydict.EasyDict(name='Matrix Noah', vendor_id=0x4D58, product_id=0x0065, interface=None)]
in_queues = [[] for k in keyboards]
in_queue_mutexes = [QtCore.QMutex() for k in keyboards]
out_queues = [[] for k in keyboards]
out_queue_mutexes = [QtCore.QMutex() for k in keyboards]


def review():
    for i, k in enumerate(keyboards):
        if k.interface:
            with QtCore.QMutexLocker(in_queue_mutexes[i]):
                while True:
                    j = [j for j, m in enumerate(in_queues[i]) if m.name == 'heartbeat']
                    if not j:
                        notify('%s is lost.' % k.name)
                        k.interface.close()
                        k.interface = None
                        break
                    m = in_queues[i][j]
                    in_queues[i].pop(j)
                    if int(m.content) == m.heartbeat:
                        break
        else:
            for j in range(16):
                try:
                    d = hid.device()
                    d.open(k.vendor_id, k.product_id)
                    d.set_nonblocking(1)
                    k.interface = d
                    k.heartbeat = 0
                    notify('%s is detected.' % k.name)
                    break
                except:
                    pass
        if k.interface:
            k.heartbeat += 1
            with QtCore.QMutexLocker(out_queue_mutexes[i]):
                out_queues[i].append(easydict.EasyDict(name='heartbeat', content=k.heartbeat))


app = QtWidgets.QApplication(sys.argv)
app.setQuitOnLastWindowClosed(False)


review_timer = QtCore.QTimer()
review_timer.timeout.connect(review)
review_timer.start(1000)


app.exec_()

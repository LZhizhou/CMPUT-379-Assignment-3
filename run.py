import subprocess, time
import threading
import queue

policy = ["FIFO", "LRU"]
page_size = [512,4096,32768]
tlb_size = [32,128,512]
program = ["./heapsort", "./quicksort", "./mergesort" ]
ins_size = ["10000","100000"]
i = [True, False]
flush = [True, False]

class mythread (threading.Thread):
    def __init__(self, p , page, tlb, pro, ins, i, flush):
        threading.Thread.__init__(self)
        self.p = p
        self.page = page
        self.tlb = tlb
        self.pro = pro
        self.ins = ins
        self.i = i
        self.flush = flush

    def run(self):
        threadLimiter.acquire()
        try:
            a = self.ins + " " + self.pro + ' ' + self.p + " page size: " + str(self.page) + " tlb size: " + str(self.tlb) + " i: " + str(
                self.i) + " flush: " + str(self.flush)
            sort = subprocess.Popen(['valgrind', '--tool=lackey', '--trace-mem=yes', str(self.pro), str(self.ins)]
                                    , stderr=subprocess.STDOUT, stdout=subprocess.PIPE)

            # f = open(a, "w")
            base = ['./valtlb379', '-p', '-i', str(self.p), str(self.page), str(self.tlb)]
            if self.i:
                base.append('-i')
            if self.flush:
                base.append('-f')
                base.append('10000')
            result = subprocess.Popen(base, stdin=sort.stdout, stdout=subprocess.PIPE)
            threadLock.acquire()
            print(a)
            print(result.stdout.readline())
            print(result.stdout.readline())
            print(result.stdout.readline())
            print("========================")
            threadLock.release()
        finally:
            threadLimiter.release()




if __name__ == "__main__":
    threadLock = threading.Lock()
    threadLimiter = threading.BoundedSemaphore(6)
    threads = []
    maxThreads = 50
    q = queue.Queue(6)
    for p in policy:
        for page in page_size:
            for tlb in tlb_size:
                for pro in program:
                    for ins in ins_size:
                        for i_or_not in i:
                            for flush_or_not in flush:
                                t = mythread(p,page,tlb, pro, ins, i_or_not, flush_or_not)
                                t.start()
                                threads.append(t)








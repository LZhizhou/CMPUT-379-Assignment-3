import subprocess, time
import threading
import queue

policy = ["FIFO", "LRU"]
page_size = [512,4096,32768]
tlb_size = [32,128,512]
program = ["./heapsort", "./quicksort", "./mergesort" ]
ins_size = ["1000", "10000", "100000"]
i = [True, False]

class mythread (threading.Thread):
    def __init__(self, p , page, tlb, pro, ins, i):
        threading.Thread.__init__(self)
        self.p = p
        self.page = page
        self.tlb = tlb
        self.pro = pro
        self.ins = ins
        self.i = i

    def run(self):
        threadLimiter.acquire()

        a = [self.ins , self.pro , self.p , str(self.page) , str(self.tlb) ,str(self.i)]
        sort = subprocess.Popen(['valgrind', '--tool=lackey', '--trace-mem=yes', str(self.pro), str(self.ins)]
                                , stderr=subprocess.STDOUT, stdout=subprocess.PIPE)

        # f = open(a, "w")
        base = ['./valtlb379', '-p', str(self.p), str(self.page), str(self.tlb)]
        if self.i:
            base.append('-i')
        result = subprocess.Popen(base, stdin=sort.stdout, stdout=subprocess.PIPE)
        threadLock.acquire()
        result.stdout.readline()
        #a.append(result.stdout.readline().decode("UTF-8").strip().split(" ")[0])
        a.append(result.stdout.readline().decode("UTF-8").strip().split(" ")[0])
        a.append(result.stdout.readline().decode("UTF-8").strip().split(" ")[0])
        for i in range(len(a)):
            print(a[i],end='')
            if (i == len(a)-1):
                print('')
            else:
                print(',',end='')
        threadLock.release()

        threadLimiter.release()




if __name__ == "__main__":
    print ("int_size,program,policy,page_size,tlb_size,i,miss,hit")
    threadLock = threading.Lock()
    threadLimiter = threading.BoundedSemaphore(12)
    for p in policy:
        for page in page_size:
            for tlb in tlb_size:
                for pro in program:
                    for ins in ins_size:
                        for i_or_not in i:
                            t = mythread(p,page,tlb, pro, ins, i_or_not)
                            t.start()








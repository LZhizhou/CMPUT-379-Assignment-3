import subprocess, time

policy = ["FIFO", "LRU"]
page_size = [512,4096,32768]
tlb_size = [32,128,512]
program = ["./heapsort", "./quicksort", "./mergesort" ]
ins_size = ["10000", "100000"]
i = [True, False]
flush = [True, False]

if __name__ == "__main__":

    for p in policy:
        for page in page_size:
            for tlb in tlb_size:
                for pro in program:
                    for ins in ins_size:
                        for i_or_not in i:
                            for flush_or_not in flush:
                                a = ins + " "+pro +' '+ p + " page size: " + str(page) + " tlb size: " + str(tlb) + " i: " + str(i_or_not) + " flush: " + str(flush_or_not)
                                sort = subprocess.Popen(['valgrind','--tool=lackey','--trace-mem=yes', str(pro), str(ins)]
                                                        , stderr=subprocess.STDOUT, stdout=subprocess.PIPE)
                                print(a)
                                #f = open(a, "w")
                                base = ['./valtlb379', '-p', '-i', str(p), str(page), str(tlb)]
                                if i_or_not:
                                    base.append('-i')
                                if flush_or_not:
                                    base.append('-f')
                                    base.append('10000')
                                result = subprocess.Popen(base, stdin=sort.stdout, stdout=subprocess.PIPE)
                                print(result.stdout.readline())
                                print(result.stdout.readline())
                                print(result.stdout.readline())
                                print("========================")






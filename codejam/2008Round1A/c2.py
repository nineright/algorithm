# alpha(n) = An+Bn*sqrt(5) = (3+sqrt(5))^n
# beta(n) = An-Bn*sqrt(5) = (3-sqrt(5))^n
import numpy

m = numpy.matrix('3,5;1,3')

def fast_exp(n):
	if n == 1:
		return m
	if n&1:
		return (m*fast_exp(n-1))%100
	else:
		tm = fast_exp(n/2)
		return (tm*tm)%1000

fin = open("C.in", "r")
fout = open("C.out", "w")
fin.readline()

cas = 1
for n in fin:
# while True:
	# n = int(raw_input())
	res = fast_exp(int(n)).tolist()
	ans = int(res[0][0]*2+999)%1000
	# a little trick cause no output with first digit equals 0
	ans = str(ans/1000.0)[2:]
	fout.write("Case #%d: %s\n"%(cas, ans))
	# print "Case #%d: %s"%(cas, ans)
	cas += 1

import numpy

m = numpy.matrix('6,-4;1,0')
def fast_exp(n):
	if n == 1:
		return m
	elif n&1:
		return (m*fast_exp(n-1))%1000
	else:
		tm = fast_exp(n/2)
		return (tm*tm)%1000

fin = open("C.in", "r")
fout = open("C.out", "w")
fin.readline()
cas = 1
for n in fin:
	res = fast_exp(int(n)-1).tolist()
	ans = (res[0][0]*6+res[0][1]*2+999)%1000
	# a little trick cause no output with first digit equals 0
	ans = str(ans/1000.0)[2:]
	fout.write("Case #%d: %s\n"%(cas, ans))
	# print "Case #%d: %s"%(cas, ans)
	cas += 1

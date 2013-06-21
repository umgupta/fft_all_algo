#!/usr/bin/python

import sys
import math
tol=2

if len(sys.argv)!=3:
	print "USAGE: ./cmp.py file1 file2"
	
try:
	file1= open(sys.argv[1],'r')
except IOError:
	print sys.argv[1]+ " not found"
	sys.exit(1)
try: 
    file2= open(sys.argv[2],'r')
except IOError:
   	print sys.argv[2]+ " not found"
	sys.exit(1)
flag=0

if (len(open(sys.argv[1],'r').readlines())!=len(open(sys.argv[2],'r').readlines())):
	print "no of lines not equal in two files"
	print "test fails"
	sys.exit(1)
fail=list()
i=len(open(sys.argv[1],'r').readlines())
line1=open(sys.argv[1],'r').readlines()
line2=open(sys.argv[2],'r').readlines()
j=0;
while j<i:
	m_ar=line1[j].split("\t")
	n_ar=line2[j].split("\t")
	j+=1	
		
	if(abs(int(m_ar[0])-int(n_ar[0]))>tol or abs(int(m_ar[1])-int(n_ar[1]))>tol):
		print "fails at line: " +str(j)
		print "diff:-"+str(max((abs(int(m_ar[0])-int(n_ar[0]))),abs(int(m_ar[1])-int(n_ar[1]))))
		fail.append(max((abs(int(m_ar[0])-int(n_ar[0]))),abs(int(m_ar[1])-int(n_ar[1]))))
		print sys.argv[1]+":"+m_ar[0]+"\t"+str(int(m_ar[1]))
		print sys.argv[2]+":"+n_ar[0]+"\t"+str(int(n_ar[1]))
		flag=1

if flag==0:
	print "pass with "+str(i)+ " lines read" 
else:
	print "max_diff: " +str(max(fail))

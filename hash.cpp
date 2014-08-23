/*
for example, if you multiply 11 with 11, you get a 1001. and 111*111 is 110001. you can get any length of 111...
result in this patern 1....1(total n-1)000...0(total n)1. it is 2n bits in total.
further more, if you multiply 100*100, you get a 100000. that means, a mutiply of xxx is in [100000, 110001].
hashing
1) h(k)=[ (a*k) mod power(2,w) ]>> (w-r)
2) universal hashing
((a*k+b) mod p) mod m -- where p is a prime larger than U(find it in polynomal time with a subfunc), a and b are random integer among (0,p-1].
*/

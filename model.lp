\ENCODING=ISO-8859-1
\Problem name: Symmetrical Traveling Salesman Problem

Minimize
 obj1: 153 X(0,1) + 510 X(0,2) + 706 X(0,3) + 966 X(0,4) + 581 X(0,5)
       + 455 X(0,6) + 70 X(0,7) + 160 X(0,8) + 372 X(0,9) + 157 X(0,10)
       + 567 X(0,11) + 342 X(0,12) + 398 X(0,13) + 422 X(1,2) + 664 X(1,3)
       + 997 X(1,4) + 598 X(1,5) + 507 X(1,6) + 197 X(1,7) + 311 X(1,8)
       + 479 X(1,9) + 310 X(1,10) + 581 X(1,11) + 417 X(1,12) + 376 X(1,13)
       + 289 X(2,3) + 744 X(2,4) + 390 X(2,5) + 437 X(2,6) + 491 X(2,7)
       + 645 X(2,8) + 880 X(2,9) + 618 X(2,10) + 374 X(2,11) + 455 X(2,12)
       + 211 X(2,13) + 491 X(3,4) + 265 X(3,5) + 410 X(3,6) + 664 X(3,7)
       + 804 X(3,8) + 1070 X(3,9) + 768 X(3,10) + 259 X(3,11) + 499 X(3,12)
       + 310 X(3,13) + 400 X(4,5) + 514 X(4,6) + 902 X(4,7) + 990 X(4,8)
       + 1261 X(4,9) + 947 X(4,10) + 418 X(4,11) + 635 X(4,12) + 636 X(4,13)
       + 168 X(5,6) + 522 X(5,7) + 634 X(5,8) + 910 X(5,9) + 593 X(5,10)
       + 19 X(5,11) + 284 X(5,12) + 239 X(5,13) + 389 X(6,7) + 482 X(6,8)
       + 757 X(6,9) + 439 X(6,10) + 163 X(6,11) + 124 X(6,12) + 232 X(6,13)
       + 154 X(7,8) + 406 X(7,9) + 133 X(7,10) + 508 X(7,11) + 273 X(7,12)
       + 355 X(7,13) + 276 X(8,9) + 43 X(8,10) + 623 X(8,11) + 358 X(8,12)
       + 498 X(8,13) + 318 X(9,10) + 898 X(9,11) + 633 X(9,12) + 761 X(9,13)
       + 582 X(10,11) + 315 X(10,12) + 464 X(10,13) + 275 X(11,12)
       + 221 X(11,13) + 247 X(12,13)
Subject To
 c_0:  X(0,1) + X(0,2) + X(0,3) + X(0,4) + X(0,5) + X(0,6) + X(0,7) + X(0,8)
       + X(0,9) + X(0,10) + X(0,11) + X(0,12) + X(0,13)  = 2
 c_1:  X(0,1) + X(1,2) + X(1,3) + X(1,4) + X(1,5) + X(1,6) + X(1,7) + X(1,8)
       + X(1,9) + X(1,10) + X(1,11) + X(1,12) + X(1,13)  = 2
 c_2:  X(0,2) + X(1,2) + X(2,3) + X(2,4) + X(2,5) + X(2,6) + X(2,7) + X(2,8)
       + X(2,9) + X(2,10) + X(2,11) + X(2,12) + X(2,13)  = 2
 c_3:  X(0,3) + X(1,3) + X(2,3) + X(3,4) + X(3,5) + X(3,6) + X(3,7) + X(3,8)
       + X(3,9) + X(3,10) + X(3,11) + X(3,12) + X(3,13)  = 2
 c_4:  X(0,4) + X(1,4) + X(2,4) + X(3,4) + X(4,5) + X(4,6) + X(4,7) + X(4,8)
       + X(4,9) + X(4,10) + X(4,11) + X(4,12) + X(4,13)  = 2
 c_5:  X(0,5) + X(1,5) + X(2,5) + X(3,5) + X(4,5) + X(5,6) + X(5,7) + X(5,8)
       + X(5,9) + X(5,10) + X(5,11) + X(5,12) + X(5,13)  = 2
 c_6:  X(0,6) + X(1,6) + X(2,6) + X(3,6) + X(4,6) + X(5,6) + X(6,7) + X(6,8)
       + X(6,9) + X(6,10) + X(6,11) + X(6,12) + X(6,13)  = 2
 c_7:  X(0,7) + X(1,7) + X(2,7) + X(3,7) + X(4,7) + X(5,7) + X(6,7) + X(7,8)
       + X(7,9) + X(7,10) + X(7,11) + X(7,12) + X(7,13)  = 2
 c_8:  X(0,8) + X(1,8) + X(2,8) + X(3,8) + X(4,8) + X(5,8) + X(6,8) + X(7,8)
       + X(8,9) + X(8,10) + X(8,11) + X(8,12) + X(8,13)  = 2
 c_9:  X(0,9) + X(1,9) + X(2,9) + X(3,9) + X(4,9) + X(5,9) + X(6,9) + X(7,9)
       + X(8,9) + X(9,10) + X(9,11) + X(9,12) + X(9,13)  = 2
 c_10: X(0,10) + X(1,10) + X(2,10) + X(3,10) + X(4,10) + X(5,10) + X(6,10)
       + X(7,10) + X(8,10) + X(9,10) + X(10,11) + X(10,12) + X(10,13)  = 2
 c_11: X(0,11) + X(1,11) + X(2,11) + X(3,11) + X(4,11) + X(5,11) + X(6,11)
       + X(7,11) + X(8,11) + X(9,11) + X(10,11) + X(11,12) + X(11,13)  = 2
 c_12: X(0,12) + X(1,12) + X(2,12) + X(3,12) + X(4,12) + X(5,12) + X(6,12)
       + X(7,12) + X(8,12) + X(9,12) + X(10,12) + X(11,12) + X(12,13)  = 2
 c_13: X(0,13) + X(1,13) + X(2,13) + X(3,13) + X(4,13) + X(5,13) + X(6,13)
       + X(7,13) + X(8,13) + X(9,13) + X(10,13) + X(11,13) + X(12,13)  = 2
Bounds
 0 <= X(0,1) <= 1
 0 <= X(0,2) <= 1
 0 <= X(0,3) <= 1
 0 <= X(0,4) <= 1
 0 <= X(0,5) <= 1
 0 <= X(0,6) <= 1
 0 <= X(0,7) <= 1
 0 <= X(0,8) <= 1
 0 <= X(0,9) <= 1
 0 <= X(0,10) <= 1
 0 <= X(0,11) <= 1
 0 <= X(0,12) <= 1
 0 <= X(0,13) <= 1
 0 <= X(1,2) <= 1
 0 <= X(1,3) <= 1
 0 <= X(1,4) <= 1
 0 <= X(1,5) <= 1
 0 <= X(1,6) <= 1
 0 <= X(1,7) <= 1
 0 <= X(1,8) <= 1
 0 <= X(1,9) <= 1
 0 <= X(1,10) <= 1
 0 <= X(1,11) <= 1
 0 <= X(1,12) <= 1
 0 <= X(1,13) <= 1
 0 <= X(2,3) <= 1
 0 <= X(2,4) <= 1
 0 <= X(2,5) <= 1
 0 <= X(2,6) <= 1
 0 <= X(2,7) <= 1
 0 <= X(2,8) <= 1
 0 <= X(2,9) <= 1
 0 <= X(2,10) <= 1
 0 <= X(2,11) <= 1
 0 <= X(2,12) <= 1
 0 <= X(2,13) <= 1
 0 <= X(3,4) <= 1
 0 <= X(3,5) <= 1
 0 <= X(3,6) <= 1
 0 <= X(3,7) <= 1
 0 <= X(3,8) <= 1
 0 <= X(3,9) <= 1
 0 <= X(3,10) <= 1
 0 <= X(3,11) <= 1
 0 <= X(3,12) <= 1
 0 <= X(3,13) <= 1
 0 <= X(4,5) <= 1
 0 <= X(4,6) <= 1
 0 <= X(4,7) <= 1
 0 <= X(4,8) <= 1
 0 <= X(4,9) <= 1
 0 <= X(4,10) <= 1
 0 <= X(4,11) <= 1
 0 <= X(4,12) <= 1
 0 <= X(4,13) <= 1
 0 <= X(5,6) <= 1
 0 <= X(5,7) <= 1
 0 <= X(5,8) <= 1
 0 <= X(5,9) <= 1
 0 <= X(5,10) <= 1
 0 <= X(5,11) <= 1
 0 <= X(5,12) <= 1
 0 <= X(5,13) <= 1
 0 <= X(6,7) <= 1
 0 <= X(6,8) <= 1
 0 <= X(6,9) <= 1
 0 <= X(6,10) <= 1
 0 <= X(6,11) <= 1
 0 <= X(6,12) <= 1
 0 <= X(6,13) <= 1
 0 <= X(7,8) <= 1
 0 <= X(7,9) <= 1
 0 <= X(7,10) <= 1
 0 <= X(7,11) <= 1
 0 <= X(7,12) <= 1
 0 <= X(7,13) <= 1
 0 <= X(8,9) <= 1
 0 <= X(8,10) <= 1
 0 <= X(8,11) <= 1
 0 <= X(8,12) <= 1
 0 <= X(8,13) <= 1
 0 <= X(9,10) <= 1
 0 <= X(9,11) <= 1
 0 <= X(9,12) <= 1
 0 <= X(9,13) <= 1
 0 <= X(10,11) <= 1
 0 <= X(10,12) <= 1
 0 <= X(10,13) <= 1
 0 <= X(11,12) <= 1
 0 <= X(11,13) <= 1
 0 <= X(12,13) <= 1
Binaries
 X(0,1)  X(0,2)  X(0,3)  X(0,4)  X(0,5)  X(0,6)  X(0,7)  X(0,8)  X(0,9) 
 X(0,10)  X(0,11)  X(0,12)  X(0,13)  X(1,2)  X(1,3)  X(1,4)  X(1,5)  X(1,6) 
 X(1,7)  X(1,8)  X(1,9)  X(1,10)  X(1,11)  X(1,12)  X(1,13)  X(2,3)  X(2,4) 
 X(2,5)  X(2,6)  X(2,7)  X(2,8)  X(2,9)  X(2,10)  X(2,11)  X(2,12)  X(2,13) 
 X(3,4)  X(3,5)  X(3,6)  X(3,7)  X(3,8)  X(3,9)  X(3,10)  X(3,11)  X(3,12) 
 X(3,13)  X(4,5)  X(4,6)  X(4,7)  X(4,8)  X(4,9)  X(4,10)  X(4,11)  X(4,12) 
 X(4,13)  X(5,6)  X(5,7)  X(5,8)  X(5,9)  X(5,10)  X(5,11)  X(5,12)  X(5,13) 
 X(6,7)  X(6,8)  X(6,9)  X(6,10)  X(6,11)  X(6,12)  X(6,13)  X(7,8)  X(7,9) 
 X(7,10)  X(7,11)  X(7,12)  X(7,13)  X(8,9)  X(8,10)  X(8,11)  X(8,12) 
 X(8,13)  X(9,10)  X(9,11)  X(9,12)  X(9,13)  X(10,11)  X(10,12)  X(10,13) 
 X(11,12)  X(11,13)  X(12,13) 
End

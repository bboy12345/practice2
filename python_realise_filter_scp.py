#!/usr/bin/python3
# Copyright 2010-2012 Microsoft Corporation
#                     Johns Hopkins University (author: Daniel Povey)

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#  http://www.apache.org/licenses/LICENSE-2.0
#
# THIS CODE IS PROVIDED *AS IS* BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
# KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION ANY IMPLIED
# WARRANTIES OR CONDITIONS OF TITLE, FITNESS FOR A PARTICULAR PURPOSE,
# MERCHANTABLITY OR NON-INFRINGEMENT.
# See the Apache 2 License for the specific language governing permissions and
# limitations under the License.


# This script takes a list of utterance-ids or any file whose first field
# of each line is an utterance-id, and filters an scp
# file (or any file whose "n-th" field is an utterance id), printing
# out only those lines whose "n-th" field is in id_list. The index of
# the "n-th" field is 1, by default, but can be changed by using
# the -f <n> switch

from ast import arg
from audioop import lin2adpcm
from operator import le
from sys import argv
import sys
import re
from tkinter.tix import Tree

exclude = 0
field = 1
shifted = 0
argv = argv[1:]  # 取出python自己的文件名
while True:
    if argv[0] == "--exclude":
        exclude = 1
        argv.pop(0)
        shifted = 1
    if argv[0] == "-f":
        field = argv[1]
        argv.pop(0)
        argv.pop(0)
        shifted = 1
    if shifted == 0:
        break
print(argv)
# 判断参数个数
if len(argv) <1 or len(argv) > 2:
    print ("Usage: filter_scp.pl [--exclude] [-f <field-to-filter-on>] id_list [in.scp] > out.scp ")
    print ("Prints only the input lines whose f'th field (default: first) is in 'id_list'.")
    print ("Note: only the first field of each line in id_list matters.  With --exclude, prints")
    print ("only the lines that were *not* in id_list.")
    print ("Caution: previously, the -f option was interpreted as a zero-based field index.")
    print ("If your older scripts (written before Oct 2014) stopped working and you used the") 
    print ("-f option, add 1 to the argument.") 
    print ("See also: utils/filter_scp.pl .")
    sys.exit(1)

idlist = argv.pop(0)
try:
    F = open(idlist, 'r', encoding="utf-8") # 只读操作
except :
    print("Could not open id-list file", idlist)
    sys.exit(1)
# <>表示按行读取文件内容
line_content = F.readline()
# 使用字典存放idlist.txt内容
seen = {}
while line_content:
    # perl中的split函数
    A = re.split("\s+", line_content)
    # 如果长度小于1报错并退出程序
    if len(A) < 1:
        print("Invalid id-list file line", line_content)
        sys.exit(1)
    seen[A[0]] = 1
    line_content = F.readline()  # 读取下一行

# 打开in.scp文件和out.scp文件
in_file = open(argv[0], "r", encoding="utf-8")
out_file = open("out.scp", "w", encoding="utf-8")
line_content2 = in_file.readline()
print(seen)
if field == 1:  # Treat this as special case, since it is common
    while line_content2:
        # perl中使用=~进行模式匹配, $_是一个内置变量
        if re.search("\s*(\S+)\s*", line_content2) == None:  # 如果无法匹配的话则报错并退出
            print("Bad line $_, could not get first field.")
            sys.exit(1)
        # $1 is what we filter on.
        first_result = re.findall("\s*(\S+)\s*", line_content2)[0]
        try:
            if (~exclude and seen[first_result]) or (exclude and ~(seen[first_result] in dir())):
                print(first_result)
                out_file.write(first_result + '\n')
        except:
            a = 1
        line_content2 = in_file.readline()
else:
    while line_content2:
        A = re.split("\s+", line_content2)
        if len(A) <= 0:
            print("Invalid scp file line", line_content2)
        if len(A) < field:
            print("Invalid scp file line", line_content2)
        if (~exclude and seen[A[field-1]]) or (exclude and ~(seen[A[field-1]] in dir())):
            print(A[field-1])
            out_file.write(A[field-1] + '\n')
        line_content2 = F.readline()

# tests:
# the following should print "foo 1"
# ( echo foo 1; echo bar 2 ) | utils/filter_scp.pl <(echo foo)
# the following should print "bar 2".
# ( echo foo 1; echo bar 2 ) | utils/filter_scp.pl -f 2 <(echo 2)
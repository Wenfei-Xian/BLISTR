import re
import sys

def extract_and_tab_separate_text_outside_tags(s):
    # 使用正则表达式找到所有的<>外的文本段
    fragments = re.split(r'<.*?>', s)
    
    # 过滤掉空字符串
    fragments = [fragment for fragment in fragments if fragment]
    
    # 使用制表符连接非空文本段
    return '\t'.join(fragments)

# 从命令行参数获取文件名
input_filename = sys.argv[1]

# 读取和处理文件
with open(input_filename, 'r') as f:
    for line in f:
        # 检查行是否以<A HREF=开头
        if line.startswith('<A HREF='):
            # 提取并用制表符分隔尖括号<>外的文本
            result = extract_and_tab_separate_text_outside_tags(line)
            
            # 分割该行成多个列
            columns = result.split('\t')
            
            # 取出第一列中的第一个空格前的内容
            first_col_content = columns[0].split(' ')[0]
            
            # 取出第8、9、10列
            eighth_col, ninth_col, tenth_col = columns[7:10]
            
            # 在第8列的字符串里，将 '-' 替换为 '\t'
            eighth_col_replaced = eighth_col.replace('-', '\t')
            
            # 组合这些列成一个新行，并用 '\t' 分隔
            new_line = '\t'.join([first_col_content, eighth_col_replaced, ninth_col, tenth_col])
            
            # 输出新行
            print(new_line)


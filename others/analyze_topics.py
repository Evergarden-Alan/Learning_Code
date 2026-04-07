#!/usr/bin/env python3
import re

def analyze_od_oj():
    with open('od_oj_text.txt', 'r', encoding='utf-8') as f:
        content = f.read()

    # 整个文本在一行中，我们需要提取题目信息
    # 格式: 序号 题目名称 考点 or 实现 分值
    # 使用正则表达式提取每个题目的信息
    # 模式: 数字+空格+非数字字符(题目名称)+空格+考点信息+空格+分值
    # 但考点可能包含多个词，如"DFS、哈希表"

    # 简单方法：按数字分割
    lines = content.split(' 点击去做题 ')

    topics = {}
    problems_by_topic = {}

    for line in lines:
        # 提取数字序号
        match = re.match(r'(\d+)\s+(.*?)\s+(.*?)\s+(\d+)分', line.strip())
        if match:
            num = match.group(1)
            name = match.group(2)
            topic = match.group(3)
            score = match.group(4)

            # 清理考点名称（可能包含"or 实现"）
            topic = topic.replace(' or 实现', '').strip()

            # 统计考点
            if topic in topics:
                topics[topic] += 1
                problems_by_topic[topic].append((num, name, score))
            else:
                topics[topic] = 1
                problems_by_topic[topic] = [(num, name, score)]

    print("考点统计:")
    for topic, count in sorted(topics.items(), key=lambda x: x[1], reverse=True):
        print(f"{topic}: {count}题")

    print("\n\n详细题目分类:")
    for topic, problems in sorted(problems_by_topic.items()):
        print(f"\n=== {topic} ({len(problems)}题) ===")
        for num, name, score in sorted(problems, key=lambda x: int(x[0])):
            print(f"{num}. {name} ({score}分)")

if __name__ == '__main__':
    analyze_od_oj()
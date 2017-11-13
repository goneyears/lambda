import requests #导入requests 模块
from bs4 import BeautifulSoup  #导入BeautifulSoup 模块

headers = {'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko)'
                         ' Chrome/54.0.2840.99 Safari/537.36'}
web_url = 'https://ziege58.deviantart.com/favourites/'
r = requests.get(web_url, headers=headers) #像目标url地址发送get请求，返回一个response对象
print(r.text)
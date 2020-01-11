import requests

head = {
    "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/54.0.2840.99 Safari/537.36"}
url = r'http://www.ituba.cc/imagesfile/2019/0826/20190826102427831.jpg'
r = requests.get(url,verify=False,headers=head)
print("执行到这一步了")
img = r.content       #响应的二进制文件
with open('picture.png','wb') as f:     #二进制写入
    f.write(img)



'''
This is a crawler.I write this just for getting some pictures from a small website.
Ok,to be honest,this crawler is aim to getting sexy girl pictures.
It can automatically download pictures in bulk,but just for one page in the main list.(You can simply get url in my code)
So,If you want to get all,you have to flip the page by yourself.
Maybe one day I will improve this crawler,But not now ~
'''

import requests
import re
from os import path, mkdir


# this function is using to get the download url of the picture.
def download(picpagetext):
    urlparrten = re.compile(r'src="(.+)" />')
    picsrc = urlparrten.search(picpagetext)
    print(picsrc.group(1))
    firstiteration = picsrc.group(1).replace('/', '')
    seconditeration = firstiteration.replace('.', '')
    filename = seconditeration.replace(':', '')
    file = open("C:\\Users\\Wu\\Desktop\\Python Project\\picture\\" + filename + '.png', 'wb+')
    pic = requests.get(picsrc.group(1), verify=False, headers=head)
    # print(pic.content)
    file.write(pic.content)
    file.close()


liburl = "http://www.ituba.cc/siwa/"
head = {
    "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/54.0.2840.99 Safari/537.36"}
listpage = requests.get(liburl, verify=False, headers=head)  # cancel the authentication of certificate
if (listpage.status_code == 200):
    print("Connect Page success.")
else:
    print("Have error in get connect with Page.")
    exit(-1)
listpagetext = listpage.text
partten1 = re.compile(r'<a href="(.*)" class="ImgBox')  # 获得每一个系列的第一张图片的url
result = partten1.findall(listpagetext)
if path.exists("C:\\Users\\Wu\\Desktop\\Python Project\\picture") == False:
    mkdir("C:\\Users\\Wu\\Desktop\\Python Project\\picture")
# print(result)
for res in result:
    picpage = requests.get(res, verify=False, headers=head)  # now,we connect to the first page of picture set.
    picpagetext = picpage.text
    # print(picpagetext)
    partten2 = re.compile(r'class="page-en">([0-9]+)</a>')  # get how many pictures in one series.
    pagenum = partten2.findall(picpagetext)

    # get the download url of the first picture.
    download(picpagetext)

    if pagenum:
        # print(pagenum[-1])
        parrten4 = re.compile(r'(.*).html')
        module = parrten4.findall(res)
        # print(module)

        '''
        now,get the main part of the url,using that to get all the pictures.
        If you carefully enough, you will find the url of pictures have patterns.
        so if we get the module,we can get all urls of a series pictures.
        '''

        for num in range(2, int(pagenum[-1]) + 1):
            urlstr = module[0] + '_' + str(num) + '.html'  # now,we get all urls.
            # print(urlstr)
            webpage = requests.get(urlstr, verify=False, headers=head)
            # print(webpage.content)
            download(webpage.text)

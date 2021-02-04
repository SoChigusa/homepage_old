# Pythonでスクレイピング

## （スクレイピングというほどでもないが）ブラウザ操作

`selenium`を使う。インストールされているChromeのバージョンに対応したWebDriverを[ダウンロードページ](https://chromedriver.chromium.org/downloads)から落としておく。

``` python
from selenium import webdriver
from selenium.webdriver.common.keys import Keys
from selenium.webdriver.support.ui import WebDriverWait

chrome = webdriver.Chrome('path-to-chrome-driver')

# ページの取得
chrome.get('URL')

# タブが閉じられるのを待つ
tmax = 60*60*24 # in seconds
WebDriverWait(chrome, tmax).until(lambda d: len(d.window_handles) == 0)

# 終了処理
chrome.quit()
```

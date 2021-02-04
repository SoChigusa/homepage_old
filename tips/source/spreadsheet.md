# Pythonを使ってGoogleスプレッドシートにアクセス

## 前準備

[このサイト](https://tanuhack.com/operate-spreadsheet/)の記述通りにやればできる。
大まかな流れとしては、

1. Google Cloud Platformでプロジェクトを作成する。
2. Google Drive APIとGoogle Sheets APIを有効にする。
3. 認証情報を作成し（サービスアカウントキーというものを選択する）、JSONタイプのキーをダウンロードする。
4. JSONファイルの中をのぞいて、`client_email`と書かれたアドレスをコピーする。
5. スプレッドシートの共有メニューから、上記のアドレスにメールを送って編集者権限でシートを共有する。このときaddress not foundエラーのメールが届くが、どうやらそれでも上手くいっているよう。

## シートを開くまで

またしても[上記サイト](https://tanuhack.com/operate-spreadsheet/)からの借り物。

``` python
import gspread
import json

#ServiceAccountCredentials：Googleの各サービスへアクセスできるservice変数を生成します。
from oauth2client.service_account import ServiceAccountCredentials

#2つのAPIを記述しないとリフレッシュトークンを3600秒毎に発行し続けなければならない
scope = ['https://spreadsheets.google.com/feeds','https://www.googleapis.com/auth/drive']

#認証情報設定
#ダウンロードしたjsonファイル名をクレデンシャル変数に設定（秘密鍵、Pythonファイルから読み込みしやすい位置に置く）
credentials = ServiceAccountCredentials.from_json_keyfile_name('ダウンロードしたJSONファイル名.json', scope)

#OAuth2の資格情報を使用してGoogle APIにログインします。
gc = gspread.authorize(credentials)

#共有設定したスプレッドシートキーを変数[SPREADSHEET_KEY]に格納する。
SPREADSHEET_KEY = 'スプレッドシートキー'

#共有設定したスプレッドシートのシート1を開く
worksheet = gc.open_by_key(SPREADSHEET_KEY).sheet1
```

JSONファイルのパスと、スプレッドシートキー（https://docs.google.com/spreadsheets/d/[Spreadsheet_Key]/edit#gid=xxx）を上のコードに埋める。

## 値の読み取り

重要なgspreadモジュールのドキュメントは[こちら](https://gspread.readthedocs.io/en/latest/)。
基本の基本は

- n行目の値をarrayで返す`worksheet.row_values(n)`
- n列目の値をarrayで返す`worksheet.col_values(n)`

# PythonとGoogle-APIで遊ぶ

## 前準備

何をおいてもGoogle Cloud Platformでプロジェクトを作成しておく。
（[参考](https://tanuhack.com/operate-spreadsheet/)）
このプロジェクト内で必要なAPIを有効にして、利用するための設定を色々と行っていく。

## Google Calendarにアクセス

[このサイト](https://non-dimension.com/python-googlecalendarapi/)やその他に書かれている通りにやろうと思ったが、なんだか[Python Quickstartのページ](https://developers.google.com/calendar/quickstart/python?hl=ja)の見た目が違う。
ということで少し遠回りしたが、大まかにやったことは、
```
pip install --upgrade google-api-python-client google-auth-httplib2 google-auth-oauthlib
```
さらに先ほど作成したプロジェクト内で
1. Google Calendar APIを有効にする。
2. [Create credentials](https://developers.google.com/workspace/guides/create-credentials?hl=ja)のページを参考にOAuth client ID credentialの作成。
3. 作成途中のユーザータイプを選ぶ箇所（ステップ6）では、「内部」が選べなかったので「外部」を選択。同時に、テストユーザーとして自分のgmailアカウントを登録しておくことで、アプリがアカウントにアクセス出来るようになる。
4. 作成途中のスコープを選ぶ箇所（ステップ11）では、Google Calendar API関連のものを全て（必要な分だけ）選択。
5. 作成した認証情報を`credential.json`の名前で保存したら、[ここ](https://developers.google.com/calendar/quickstart/python?hl=ja)にある通り`quickstart.py`の実行。初回実行時にアプリを認証すれば、`token.json`が作成されて二度目以降は認証がいらなくなる。

### カレンダーに書き込むプログラム

[上記サイト](https://non-dimension.com/python-googlecalendarapi/)からの借り物。

``` python
from __future__ import print_function
import datetime
import pickle
import os.path
from googleapiclient.discovery import build
from google_auth_oauthlib.flow import InstalledAppFlow
from google.auth.transport.requests import Request

# If modifying these scopes, delete the file token.pickle.
SCOPES = ['https://www.googleapis.com/auth/calendar']

def main():
    creds = None
    # The file token.pickle stores the user's access and refresh tokens, and is
    # created automatically when the authorization flow completes for the first
    # time.
    if os.path.exists('token.pickle'):
        with open('token.pickle', 'rb') as token:
            creds = pickle.load(token)
    # If there are no (valid) credentials available, let the user log in.
    if not creds or not creds.valid:
        if creds and creds.expired and creds.refresh_token:
            creds.refresh(Request())
        else:
            flow = InstalledAppFlow.from_client_secrets_file(
                'credentials.json', SCOPES)
            creds = flow.run_local_server(port=0)
        # Save the credentials for the next run
        with open('token.pickle', 'wb') as token:
            pickle.dump(creds, token)

    service = build('calendar', 'v3', credentials=creds)

    event = {
      'summary': '予定1',
      'location': 'Shibuya Office',
      'description': 'サンプルの予定',
      'start': {
        'dateTime': '2019-09-10T09:00:00',
        'timeZone': 'Japan',
      },
      'end': {
        'dateTime': '2019-09-10T17:00:00',
        'timeZone': 'Japan',
      },
    }

    event = service.events().insert(calendarId='コピーしたIDを貼り付け',
                                    body=event).execute()
    print (event['id'])

if __name__ == '__main__':
    main()
```

`SCOPES`を読み込みのみから書き込みありに変更しているので、`token.json`を一度削除して作り直すのを忘れない。

## スプレッドシートの利用

[このサイト](https://tanuhack.com/operate-spreadsheet/)の記述通りにやればできる。
大まかな流れとしては、先ほど作成したプロジェクト内で
1. Google Drive APIとGoogle Sheets APIを有効にする。
2. 認証情報を作成し（サービスアカウントキーというものを選択する）、JSONタイプのキーをダウンロードする。
3. JSONファイルの中をのぞいて、`client_email`と書かれたアドレスをコピーする。
4. スプレッドシートの共有メニューから、上記のアドレスにメールを送って編集者権限でシートを共有する。このときaddress not foundエラーのメールが届くが、どうやらそれでも上手くいっているよう。

### シートを開くまで

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

### 値の読み取り

重要なgspreadモジュールのドキュメントは[こちら](https://gspread.readthedocs.io/en/latest/)。
基本の基本は

- n行目の値をarrayで返す`worksheet.row_values(n)`
- n列目の値をarrayで返す`worksheet.col_values(n)`

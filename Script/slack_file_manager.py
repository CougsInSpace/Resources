##########
# Forked from: https://github.com/marek/fslack
# Refactored by: Cody Sigvartson at https://github.com/CodySigvartson?tab=repositories
# Property of Cougs in Space - Washington State University
##########

#!/usr/bin/env python3
import requests
import shutil
import json
import argparse
import calendar
import errno
import sys
import os
from datetime import datetime, timedelta

# Constants
API = "https://slack.com/api"

# Settings
parser = argparse.ArgumentParser(description="Download/Delete files.")
parser.add_argument("token", help="API Token: see https://api.slack.com/web")
parser.add_argument("-o", "--out", default='.', help="Output folder")
parser.add_argument("--all", default=False, action="store_true", help="Download all of the organizations files?")
parser.add_argument("--download", default=False, action="store_true", help="Download files?")
parser.add_argument("--delete", default=False, action="store_true", help="Delete files?")
args = parser.parse_args()

if not (args.download or  args.delete):
    print("Must select at least one of --download or --delete")
    sys.exit(errno.EINVAL)

def download_file(url, out, channel):
    local_filename = out + '\\' + channel
    try:
        os.stat(local_filename)
    except:
        os.mkdir(local_filename)

    local_filename = out + '\\' + channel + '\\' + url.split('/')[-1]
    print("outputting to file: %s" % local_filename)

    response = requests.get(url, stream=True, headers={"Authorization" : "Bearer " + args.token})
    with open(local_filename, "wb") as f:
        response.raw.decode_content = True
        shutil.copyfileobj(response.raw,f)
    return local_filename


def get_files(page):
    list_url = API+"/files.list"

    print("Requesting all files")
    data = {"token": args.token, "page": page}
    response = requests.post(list_url, data=data)
    if response.status_code != requests.codes.ok:
        print("Error fetching file list")
        sys.exit(1)
    return response.json()


if __name__ == "__main__":
    page = 1
    num_files_downloaded = 0
    file_download_fail = 0
    total_files = 0
    while True:
        json = get_files(page)
        if not json["ok"]:
            print("Error", json["error"])

        fileCount = len(json["files"])
        print("Found", fileCount, "files")
        if fileCount == 0:
            break

        for f in json["files"]:
            total_files = total_files + 1
            if args.download:
                try:
                    file_url = f["url_private_download"]
                    print("Downloading file: '%s'" % file_url)
                    download_file(file_url, args.out, channel)
                    num_files_downloaded = num_files_downloaded + 1
                except:
                    print("File not downloadable")
                    file_download_fail = file_download_fail + 1

                if (len(f["channels"]) > 0):
                    channel = f["channels"][0]
                else:
                    channel = ""

            if args.delete:
                data = { "token": args.token, "file": f["id"], "set_active": "true", "_attempts": "1"}
                timestamp = str(calendar.timegm(datetime.now().utctimetuple()))
                delete_url = API+"/files.delete?t="+timestamp
                requests.post(delete_url, data=data,headers={"Authorization" : "Bearer " + args.token})

        page = page + 1
    print(f"Files found: {total_files} Files processed: {num_files_downloaded} Failed file processes: {file_download_fail}")
    print("Finished.")

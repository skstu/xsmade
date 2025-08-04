import http.server
import socketserver
import os
import datetime

PORT = 8080

DIRECTORY = os.path.dirname(os.path.abspath(__file__))
LOGS_DIR = os.path.join(DIRECTORY, "logs")
# 启动时主动创建 logs 文件夹
if not os.path.exists(LOGS_DIR):
    try:
        os.makedirs(LOGS_DIR)
        print(f"[INFO] logs 文件夹已创建: {LOGS_DIR}")
    except Exception as e:
        print(f"[ERROR] 创建 logs 文件夹失败: {e}")
else:
    print(f"[INFO] logs 文件夹已存在: {LOGS_DIR}")


class Handler(http.server.SimpleHTTPRequestHandler):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, directory=DIRECTORY, **kwargs)


    def do_OPTIONS(self):
        if self.path == "/ub":
            self.send_response(200)
            self.send_header("Access-Control-Allow-Origin", "*")
            self.send_header("Access-Control-Allow-Methods", "POST, OPTIONS")
            self.send_header("Access-Control-Allow-Headers", "Content-Type")
            self.end_headers()
        else:
            super().do_OPTIONS()

    def do_POST(self):
        if self.path == "/ub":
            try:
                content_length = int(self.headers.get('Content-Length', 0))
                post_data = self.rfile.read(content_length)
                print("Received /ub data:", post_data.decode('utf-8'))

                # 生成时间戳文件名
                timestamp = datetime.datetime.now().strftime(
                    "%Y%m%d_%H%M%S_%f")[:-3]  # 精确到毫秒
                filename = f"{timestamp}.json"
                filepath = os.path.join(LOGS_DIR, filename)

                # 保存到文件
                with open(filepath, "w", encoding="utf-8") as f:
                    f.write(post_data.decode('utf-8'))

                print(f"[INFO] Data saved to: {filepath}")
                self.send_response(200)
                self.send_header("Content-Type", "application/json")
                self.send_header("Access-Control-Allow-Origin", "*")
                self.end_headers()
                self.wfile.write(b'{"status":"ok"}')
            except Exception as e:
                print(f"[ERROR] 处理POST请求或写文件失败: {e}")
                self.send_response(500)
                self.end_headers()
                self.wfile.write(b'{"status":"error"}')
        else:
            super().do_POST()


if __name__ == "__main__":
    with socketserver.TCPServer(("", PORT), Handler) as httpd:
        print(f"Serving at http://127.0.0.1:{PORT}/adscore.html")
        httpd.serve_forever()

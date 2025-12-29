# Qt Image Processor

一個基於 Qt 5 的影像處理應用程式，提供影像載入、顯示、縮放、幾何轉換以及區域選取放大與編輯功能。

A Qt 5-based image processing application that provides image loading, display, zoom, geometric transformations, and region selection with editing capabilities.

## 功能特色 (Features)

### 基本功能 (Basic Features)
- 📂 開啟與顯示影像檔案 (BMP, PNG, JPEG)
- 🔍 影像放大與縮小
- 🔄 幾何轉換（鏡射、旋轉）
- 💾 影像儲存

### 新增功能 (New Features)
- 🖱️ **即時灰階值顯示**: 移動滑鼠時顯示游標位置及該點的灰階值
- ✂️ **區域選取放大**: 可拖移或點擊選取區域進行放大
- 🔢 **自訂放大倍率**: 支援 0.1x 至 10.0x 的自訂放大倍率
- 🪟 **獨立放大視窗**: 選取的區域會在新視窗中顯示
- 🎨 **畫筆工具**: 可在放大視窗中使用畫筆編輯影像
  - 可調整筆刷大小 (1-50 像素)
  - 可選擇筆刷顏色
  - 支援連續繪製
- 💾 **另存新檔**: 可將編輯後的影像儲存為 PNG、JPEG 或 BMP 格式

## 系統需求 (Requirements)

- Qt 5.x
- C++17 compiler
- Linux / Windows / macOS

## 編譯與安裝 (Build & Installation)

### Linux

```bash
# 安裝 Qt 5 開發環境
sudo apt-get install qt5-qmake qtbase5-dev

# 編譯專案
qmake Qt_imageprocessor.pro
make

# 執行程式
./Qt_imageprocessor
```

### Windows

1. 安裝 Qt 5 和 Qt Creator
2. 開啟 `Qt_imageprocessor.pro`
3. 點擊建置 (Build)
4. 執行程式

## 使用方式 (Usage)

### 1. 載入影像 (Load Image)
- 點擊 "開啟檔案" 或按 `Ctrl+O`
- 選擇影像檔案 (BMP, PNG, JPEG)

### 2. 查看灰階值 (View Grayscale Values)
- 將滑鼠移動到影像上
- 狀態列會顯示: `(x, y) Gray: 值`
- 白色像素顯示 255，黑色像素顯示 0

### 3. 選取區域放大 (Select Region to Zoom)
1. 在影像上按住滑鼠左鍵
2. 拖曳以建立選取矩形（會顯示藍色虛線框）
3. 放開滑鼠按鈕
4. 在對話框中輸入放大倍率（0.1 - 10.0）
5. 點擊確定，新視窗會顯示放大的區域

### 4. 使用畫筆工具 (Use Brush Tool)
在放大視窗中：
1. 點擊 "畫筆模式" 按鈕啟用繪圖
2. 使用 "筆刷大小" 調整筆刷大小（1-50）
3. 點擊 "選擇顏色" 選擇顏色
4. 按住左鍵並拖曳以繪圖

### 5. 儲存編輯後的影像 (Save Edited Image)
- 在放大視窗中點擊 "另存新檔" 或按 `Ctrl+S`
- 選擇儲存位置和格式（PNG / JPEG / BMP）
- 點擊儲存

## 檔案結構 (File Structure)

```
Qt_imageprocessor/
├── main.cpp              # 主程式進入點
├── img.h/cpp            # 主視窗類別（影像顯示與區域選取）
├── mouseevent.h/cpp     # 滑鼠事件處理基礎類別
├── gtransform.h/cpp     # 幾何轉換視窗
├── zoomwindow.h/cpp     # 放大視窗類別（包含畫筆工具）
├── Qt_imageprocessor.pro # Qt 專案檔
├── IMPLEMENTATION_SUMMARY.md # 實作摘要
├── TESTING_GUIDE.md     # 測試指南
├── FEATURES.md          # 功能詳細說明
└── README.md           # 本文件
```

## 快捷鍵 (Keyboard Shortcuts)

| 快捷鍵 | 功能 |
|--------|------|
| `Ctrl+O` | 開啟檔案 |
| `Ctrl+Q` | 結束程式 |
| `Ctrl+G` | 幾何轉換 |
| `Ctrl++` | 放大影像 |
| `Ctrl+-` | 縮小影像 |
| `Ctrl+S` | 另存新檔（在放大視窗中） |

## 技術細節 (Technical Details)

### 架構 (Architecture)
- **主視窗 (IMG)**: 繼承自 MouseEvent，處理影像顯示與區域選取
- **放大視窗 (ZoomWindow)**: 獨立的 QMainWindow，提供影像編輯功能
- **幾何轉換 (GTransform)**: 提供鏡射與旋轉功能

### 影像處理 (Image Processing)
- 使用 Qt 的 QImage 類別
- 灰階轉換使用 qGray() 函式（標準亮度公式）
- 影像縮放使用 Qt::SmoothTransformation（高品質）

### 座標轉換 (Coordinate Transformation)
- 視窗座標 → 影像元件座標
- 影像元件座標 → 影像像素座標
- 確保精確的灰階值讀取與區域選取

## 範例工作流程 (Example Workflows)

### 影像檢查 (Image Inspection)
1. 開啟影像
2. 移動滑鼠查看各處灰階值
3. 找到感興趣的區域
4. 選取區域並放大 3 倍
5. 在放大視窗中仔細檢查細節

### 影像標註 (Image Annotation)
1. 開啟影像
2. 選取需要標註的區域
3. 選擇適當的放大倍率（2-5x）
4. 啟用畫筆模式
5. 選擇標記顏色（紅色表示錯誤，綠色表示正確）
6. 標註重點
7. 儲存標註後的影像

### 區域比較 (Region Comparison)
1. 開啟影像
2. 選取區域 A 並放大 3x
3. 不關閉放大視窗，回到主視窗
4. 選取區域 B（相同大小）並放大 3x
5. 並排比較兩個視窗
6. 在各視窗中標註差異
7. 分別儲存兩個視窗的影像

## 測試 (Testing)

詳細的測試案例請參考 [TESTING_GUIDE.md](TESTING_GUIDE.md)，包含 20 個測試案例涵蓋：
- 基本功能測試
- 區域選取測試
- 畫筆工具測試
- 檔案儲存測試
- 邊界條件測試
- 壓力測試

## 已知限制 (Known Limitations)

1. 這是 GUI 應用程式，無法在無頭環境中執行
2. 大型影像（>5000x5000 像素）可能影響效能
3. 繪圖效能取決於系統能力
4. 每個選取必須至少 10x10 像素

## 貢獻 (Contributing)

歡迎提交問題報告和拉取請求！

## 授權 (License)

請參考專案授權文件。

## 變更日誌 (Changelog)

### v2.0 (Current)
- ✨ 新增即時灰階值顯示功能
- ✨ 新增區域選取放大功能
- ✨ 新增自訂放大倍率
- ✨ 新增獨立放大視窗
- ✨ 新增畫筆工具（可調大小與顏色）
- ✨ 新增放大視窗的另存新檔功能
- 🐛 修復記憶體洩漏問題
- 🐛 修復工具列重複建立問題
- 🐛 改善座標映射邏輯
- 📝 新增完整文件

### v1.0 (Original)
- 基本影像載入與顯示
- 固定倍率放大縮小
- 幾何轉換功能

## 聯絡資訊 (Contact)

如有問題或建議，請透過 GitHub Issues 回報。

---

**Happy Image Processing! 🖼️✨**

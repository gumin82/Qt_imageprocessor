# Testing Guide for Qt Image Processor

## Prerequisites
- Qt 5 development environment installed
- The application compiled successfully (`./Qt_imageprocessor` executable created)
- Test images available (e.g., `test_image.png` included in repository)

## Build Instructions

```bash
# Clean previous build
make clean

# Generate Makefile
qmake Qt_imageprocessor.pro

# Build
make

# The executable will be created: ./Qt_imageprocessor
```

## Test Cases

### Test 1: Launch Application
**Objective:** Verify the application starts without errors

**Steps:**
1. Run `./Qt_imageprocessor`
2. Main window should open with title "影像處理"
3. Status bar should be visible at bottom
4. Menu bar should show "檔案(&F)" and "工具(&T)" menus
5. Toolbar should display action buttons

**Expected Result:** Application launches successfully with all UI elements visible

---

### Test 2: Load Image
**Objective:** Test image loading functionality

**Steps:**
1. Click "開啟檔案" button or press Ctrl+O
2. Navigate to test image (e.g., `test_image.png`)
3. Select and open the image

**Expected Result:** 
- Image displays in the main window
- Image is properly scaled to fit the window

---

### Test 3: Grayscale Value Display
**Objective:** Verify grayscale values are shown when hovering over image

**Steps:**
1. Load an image (use Test 2)
2. Move mouse cursor over different parts of the image
3. Observe the status bar (bottom right corner)

**Expected Result:**
- Status bar shows format: "(x, y) Gray: value"
- x, y change as mouse moves
- Gray value changes based on pixel brightness (0-255)
- For test_image.png (gradient):
  - Left side (white) should show Gray: ~255
  - Right side (black) should show Gray: ~0
  - Middle should show Gray: ~128

---

### Test 4: Region Selection
**Objective:** Test selection rectangle drawing

**Steps:**
1. Load an image
2. Click and hold left mouse button on the image
3. Drag to create a rectangle
4. Observe the blue dashed rectangle appears
5. Continue dragging to different positions
6. Release mouse button

**Expected Result:**
- Blue dashed rectangle appears while dragging
- Rectangle updates in real-time as mouse moves
- Rectangle follows cursor accurately
- Status bar shows "選取區域開始: (x, y)" when starting selection

---

### Test 5: Custom Zoom Factor
**Objective:** Test zoom factor input dialog

**Steps:**
1. Load an image
2. Select a region (click, drag, release)
3. Dialog appears asking for zoom factor
4. Test different values:
   - Try 0.5 (should work)
   - Try 2.0 (default, should work)
   - Try 5.0 (should work)
   - Try 10.0 (maximum, should work)
   - Try 0.09 (below minimum, should be rejected)
   - Try 11.0 (above maximum, should be rejected)
5. Click OK after entering valid value

**Expected Result:**
- Dialog title: "選擇放大倍率"
- Default value: 2.0
- Accepts values between 0.1 and 10.0
- Rejects values outside range
- Clicking Cancel dismisses dialog without opening zoom window

---

### Test 6: Zoom Window Creation
**Objective:** Verify zoom window opens with zoomed region

**Steps:**
1. Load an image
2. Select a small region (e.g., 50x50 pixels from center)
3. Enter zoom factor 3.0
4. Click OK

**Expected Result:**
- New window opens with title "放大視窗"
- Selected region is displayed at 3x magnification
- Image quality is maintained (smooth scaling)
- Window has its own menu bar and toolbar
- Original window remains open and functional

---

### Test 7: Multiple Zoom Windows
**Objective:** Test multiple zoom windows can coexist

**Steps:**
1. Load an image
2. Create first zoom window (select region, zoom 2x)
3. Return to main window
4. Create second zoom window (select different region, zoom 3x)
5. Both zoom windows should remain open

**Expected Result:**
- Multiple zoom windows can be created
- Each displays different region at different zoom
- All windows operate independently
- Closing one doesn't affect others

---

### Test 8: Brush Tool Activation
**Objective:** Test enabling/disabling brush mode

**Steps:**
1. Create a zoom window (any region, any zoom)
2. Click "畫筆模式" button in toolbar
3. Observe cursor changes to cross
4. Status bar should show "畫筆模式已啟用"
5. Click "畫筆模式" again to toggle off
6. Cursor returns to normal arrow
7. Status bar shows "畫筆模式已關閉"

**Expected Result:**
- Brush mode toggles on/off correctly
- Cursor changes provide visual feedback
- Status messages confirm state changes

---

### Test 9: Brush Size Adjustment
**Objective:** Test brush size control

**Steps:**
1. Create zoom window and enable brush mode
2. Locate brush size spinbox in toolbar (labeled "筆刷大小")
3. Test different values:
   - Set to 1 (minimum)
   - Set to 10
   - Set to 25
   - Set to 50 (maximum)
4. Draw with each size to observe differences

**Expected Result:**
- Spinbox accepts values 1-50
- Values outside range are clamped
- Drawing line thickness matches selected size

---

### Test 10: Brush Color Selection
**Objective:** Test color picker

**Steps:**
1. Create zoom window and enable brush mode
2. Click "選擇顏色" button
3. Color picker dialog opens
4. Select red color
5. Click OK
6. Draw on image (should draw in red)
7. Repeat with different colors: blue, green, yellow

**Expected Result:**
- Color picker dialog opens
- Selected color is applied to brush
- Drawing uses selected color
- Multiple color changes work correctly

---

### Test 11: Drawing on Image
**Objective:** Test actual drawing functionality

**Steps:**
1. Create zoom window with 3x zoom
2. Enable brush mode
3. Set brush size to 10
4. Select red color
5. Click and drag to draw lines
6. Draw: straight line, curved line, circle shape
7. Release mouse, click elsewhere and draw again
8. Draw continuously without releasing

**Expected Result:**
- Lines appear as mouse is dragged
- Lines are smooth and continuous
- Line color matches selected color
- Line width matches selected brush size
- Can draw multiple separate strokes
- Drawing is permanent on the image

---

### Test 12: Save Edited Image
**Objective:** Test save functionality

**Steps:**
1. Create zoom window
2. Enable brush mode and draw something on the image
3. Click "另存新檔" or press Ctrl+S
4. Save dialog appears
5. Choose location and enter filename
6. Test different formats:
   - Save as PNG
   - Save as JPEG
   - Save as BMP
7. Click Save

**Expected Result:**
- Save dialog shows format options
- File is saved successfully
- Success message displays
- Saved file can be opened in other image viewers
- Saved file contains the drawn modifications

---

### Test 13: Save Without Drawing
**Objective:** Test saving unmodified zoom

**Steps:**
1. Create zoom window (don't draw anything)
2. Click "另存新檔"
3. Save the image

**Expected Result:**
- Zoomed image is saved successfully
- Saved image matches what's displayed in zoom window
- No error occurs

---

### Test 14: Edge Cases - Very Small Selection
**Objective:** Test minimum selection size

**Steps:**
1. Load an image
2. Try to select very small region (e.g., 5x5 pixels)
3. Release mouse

**Expected Result:**
- Selection smaller than 10x10 pixels is ignored
- No zoom window opens
- No error occurs

---

### Test 15: Edge Cases - Full Image Selection
**Objective:** Test selecting entire image

**Steps:**
1. Load an image
2. Click at top-left corner
3. Drag to bottom-right corner
4. Release and enter zoom factor 2.0

**Expected Result:**
- Entire image is selected
- Zoom window shows full image at 2x size
- No clipping or errors occur

---

### Test 16: Edge Cases - Selection Outside Image
**Objective:** Test selection extending beyond image bounds

**Steps:**
1. Load an image
2. Start selection on image
3. Drag outside the image area
4. Release mouse

**Expected Result:**
- Selection is automatically clamped to image bounds
- Only the portion within image is zoomed
- No errors occur

---

### Test 17: Grayscale on Different Image Types
**Objective:** Test grayscale calculation on various images

**Steps:**
1. Test with pure white image (create with imagemagick: `convert -size 100x100 xc:white white.png`)
2. Hover over it - should show Gray: 255
3. Test with pure black image (create: `convert -size 100x100 xc:black black.png`)
4. Hover over it - should show Gray: 0
5. Test with colored image
6. Gray value should represent luminance

**Expected Result:**
- White pixels show Gray: 255
- Black pixels show Gray: 0
- Colored pixels show appropriate grayscale conversion
- RGB color images converted correctly using luminance formula

---

### Test 18: Window Management
**Objective:** Test closing windows in different orders

**Steps:**
1. Open main window
2. Load image
3. Create zoom window 1
4. Create zoom window 2
5. Close zoom window 1
6. Close main window
7. Check if zoom window 2 stays open

**Expected Result:**
- Closing zoom window doesn't close main window
- Closing main window doesn't force close zoom windows
- Each window operates independently
- Application exits when all windows are closed

---

### Test 19: Menu Shortcuts
**Objective:** Verify keyboard shortcuts work

**Steps:**
1. Test Ctrl+O (Open file)
2. In zoom window, test Ctrl+S (Save As)
3. Test other menu shortcuts

**Expected Result:**
- All shortcuts work as documented
- Menu items show shortcut hints
- Shortcuts work even when menu is not open

---

### Test 20: Stress Test - Multiple Operations
**Objective:** Test system stability under multiple operations

**Steps:**
1. Load large image (if available)
2. Create 5 zoom windows with different regions
3. In each window:
   - Enable brush mode
   - Draw extensively
   - Change colors multiple times
   - Change brush sizes
4. Save from multiple windows
5. Create more zoom windows

**Expected Result:**
- Application remains stable
- No memory leaks evident
- All operations complete successfully
- UI remains responsive

---

## Test Results Template

For each test, record:
- **Test ID**: Test number
- **Date**: When tested
- **Tester**: Who performed the test
- **Result**: Pass/Fail
- **Notes**: Any observations or issues
- **Screenshot**: If applicable

## Known Limitations

1. This is a GUI application - automated testing requires Qt Test framework
2. Headless environments cannot display the GUI
3. Performance may vary with very large images (>5000x5000 pixels)
4. Drawing performance depends on system capabilities

## Reporting Issues

If any test fails, please report:
1. Which test failed
2. Steps to reproduce
3. Expected vs actual behavior
4. System information (OS, Qt version)
5. Screenshots or error messages

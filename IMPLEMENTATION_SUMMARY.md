# Qt Image Processor - Implementation Summary

## Features Implemented

### 1. Grayscale Value Display ✓
**Location:** `img.cpp` - `mouseMoveEvent()` function
**Description:** When moving the mouse over an image, the status bar now displays:
- Cursor position (x, y coordinates)
- Grayscale value at that pixel location

**Implementation:**
- Maps cursor position from widget coordinates to image coordinates
- Uses `qGray()` to calculate grayscale value from RGB pixel
- Updates the status bar in real-time

### 2. Region Selection by Dragging ✓
**Location:** `img.cpp` - `mousePressEvent()`, `mouseMoveEvent()`, `mouseReleaseEvent()`, `paintEvent()`
**Description:** Users can click and drag on the main window to select a region for zooming.

**Implementation:**
- `mousePressEvent()`: Starts selection when left mouse button is pressed on image
- `mouseMoveEvent()`: Updates selection rectangle while dragging
- `paintEvent()`: Draws a blue dashed rectangle to show the selection area
- `mouseReleaseEvent()`: Processes the selection and opens zoom window

### 3. Custom Zoom Magnification ✓
**Location:** `img.cpp` - `mouseReleaseEvent()`
**Description:** When a region is selected, a dialog prompts the user to enter a custom zoom factor (0.1x to 10.0x).

**Implementation:**
- Uses `QInputDialog::getDouble()` to get zoom factor from user
- Default: 2.0x
- Range: 0.1x to 10.0x with 1 decimal precision

### 4. New Zoom Window ✓
**Location:** `zoomwindow.h` and `zoomwindow.cpp`
**Description:** A new window class (`ZoomWindow`) that displays the zoomed region.

**Features of ZoomWindow:**
- Displays the selected region at the specified magnification
- Independent window with its own menu and toolbar
- Supports image editing with brush tool
- Can save edited images

### 5. Save As Functionality ✓
**Location:** `zoomwindow.cpp` - `saveImageAs()` function
**Description:** The zoom window includes a "Save As" feature accessible from menu and toolbar.

**Implementation:**
- Menu: 檔案(&F) → 另存新檔
- Shortcut: Ctrl+S
- Supports multiple formats: PNG, JPEG, BMP
- Shows success/error message after save operation

### 6. Brush/Paint Tool ✓
**Location:** `zoomwindow.cpp` - Paint-related functions
**Description:** The zoom window includes a brush tool for editing the zoomed image.

**Features:**
- Toggle brush mode: Menu → 工具(&T) → 畫筆模式 (checkable action)
- Adjustable brush size: Spinbox in toolbar (1-50 pixels)
- Color selection: Button in toolbar to choose brush color
- Visual feedback: Cursor changes to cross when in draw mode
- Drawing: Click and drag to draw on the image with selected color and size

**Implementation:**
- `toggleDrawMode()`: Enables/disables drawing mode
- `selectBrushColor()`: Opens color picker dialog
- `setBrushSize()`: Changes brush size
- `mousePressEvent()`, `mouseMoveEvent()`, `mouseReleaseEvent()`: Handle drawing logic

## File Changes

### New Files Created:
1. **zoomwindow.h** - Header file for ZoomWindow class
2. **zoomwindow.cpp** - Implementation of ZoomWindow class

### Modified Files:
1. **img.h** - Added:
   - Include for zoomwindow.h
   - paintEvent() declaration
   - Selection-related member variables (selecting, selectionStart, selectionEnd, selectionRect)

2. **img.cpp** - Modified:
   - Added includes: QPainter, QInputDialog
   - Constructor: Initialize selection variables, enable mouse tracking on imgWin
   - mouseMoveEvent(): Added grayscale value display and selection rectangle update
   - mousePressEvent(): Added selection start logic
   - mouseReleaseEvent(): Added selection processing and zoom window creation
   - paintEvent(): New function to draw selection rectangle

3. **Qt_imageprocessor.pro** - Added:
   - zoomwindow.cpp to SOURCES
   - zoomwindow.h to HEADERS

4. **.gitignore** - Added:
   - Build artifacts (Qt_imageprocessor, Makefile, moc_*.cpp, etc.)
   - Debug and release directories

## How to Build

```bash
# Generate Makefile
qmake Qt_imageprocessor.pro

# Build the project
make

# Run the application
./Qt_imageprocessor
```

## How to Use

### 1. Load an Image
- Click "開啟檔案" (Open File) button or use Ctrl+O
- Select an image file (BMP, PNG, or JPEG)

### 2. View Grayscale Values
- Move your mouse over the image
- The status bar (bottom right) will show cursor position and grayscale value
- Example: "(150, 200) Gray: 128"

### 3. Zoom into a Region
1. Click and hold the left mouse button on the image
2. Drag to create a selection rectangle (shown as blue dashed line)
3. Release the mouse button
4. A dialog will appear asking for zoom magnification (default: 2.0x)
5. Enter desired zoom factor (0.1 to 10.0) and click OK
6. A new window will open showing the zoomed region

### 4. Edit the Zoomed Image
In the zoom window:
1. Click "畫筆模式" (Brush Mode) in toolbar to enable drawing
2. Adjust brush size using the spinbox (1-50)
3. Click "選擇顏色" (Select Color) to choose brush color
4. Click and drag on the image to draw

### 5. Save the Edited Image
In the zoom window:
1. Click "另存新檔" (Save As) or press Ctrl+S
2. Choose location and format (PNG, JPEG, or BMP)
3. Click Save

## Technical Details

### Architecture
- Main window (`IMG`) extends `MouseEvent` which extends `QMainWindow`
- Zoom window (`ZoomWindow`) extends `QMainWindow` independently
- Image processing uses Qt's `QImage` class
- Grayscale calculation uses Qt's `qGray()` function

### Coordinate Mapping
The implementation carefully handles coordinate transformations:
1. Widget coordinates → Image widget coordinates (using `mapFrom()`)
2. Image widget coordinates → Image pixel coordinates (using scaling factors)
3. This ensures accurate grayscale value reading and region selection

### User Experience
- Real-time visual feedback for selection (blue dashed rectangle)
- Cursor changes to cross in draw mode
- Status bar messages for user actions
- Input validation for zoom factor
- Success/error messages for save operations

## Testing

The application has been compiled successfully without errors or warnings (except one pre-existing indentation warning in `showGeometryTransform()`).

Build output confirms all components compiled and linked correctly:
- Main window with mouse event handling
- Zoom window with brush tool
- All Qt meta-object code (MOC) generated successfully

A test gradient image (`test_image.png`) has been created for testing purposes.

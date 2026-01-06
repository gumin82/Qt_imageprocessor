# Feature Overview

## What Has Been Implemented

This document provides a summary of all features added to the Qt Image Processor application.

---

## 1. Real-time Grayscale Value Display

### Feature Description
As you move your mouse over an image, the application now displays:
- **Cursor Position**: X and Y coordinates
- **Grayscale Value**: Pixel brightness (0-255)

### Location
Status bar at the bottom right of the main window

### Format
```
(x, y) Gray: value
Example: (150, 200) Gray: 128
```

### Use Cases
- Analyzing image brightness distribution
- Finding specific pixel values for image processing
- Educational purposes for understanding grayscale conversion
- Quality control for image editing

### Technical Details
- Uses Qt's `qGray()` function for accurate luminance calculation
- Handles coordinate transformation from widget to image space
- Updates in real-time with mouse movement
- Works with any image format supported by Qt

---

## 2. Interactive Region Selection

### Feature Description
Click and drag on any loaded image to select a rectangular region for zooming.

### Visual Feedback
- **Selection Rectangle**: Blue dashed outline
- **Real-time Update**: Rectangle follows mouse cursor
- **Status Message**: Shows "選取區域開始: (x, y)" when selection starts

### How to Use
1. Load an image
2. Click left mouse button on desired start point
3. Hold and drag to define region
4. Release mouse button to complete selection

### Constraints
- Minimum selection size: 10x10 pixels
- Automatically clamped to image boundaries
- Selection outside image area is ignored

---

## 3. Custom Zoom Magnification

### Feature Description
After selecting a region, a dialog prompts for custom zoom magnification.

### Dialog Details
- **Title**: "選擇放大倍率" (Select Magnification)
- **Default Value**: 2.0x
- **Range**: 0.1x to 10.0x
- **Precision**: 1 decimal place
- **Buttons**: OK / Cancel

### Zoom Options
- **0.1x - 0.9x**: Reduce region size (useful for overview)
- **1.0x**: Original size
- **1.1x - 3.0x**: Moderate enlargement (most common)
- **3.1x - 10.0x**: High magnification (for detailed inspection)

### Use Cases
- **2x-3x**: General image inspection
- **5x-10x**: Pixel-level analysis
- **0.5x-1x**: Fitting large regions in window

---

## 4. Independent Zoom Windows

### Feature Description
Each selected region opens in a new, independent window.

### Window Features
- **Title**: "放大視窗" (Zoom Window)
- **Menu Bar**: File and Tools menus
- **Toolbar**: Quick access buttons
- **Status Bar**: Action feedback
- **Independent Operation**: Each window works separately

### Capabilities
- Multiple zoom windows can coexist
- Each window can have different zoom levels
- Each window can be edited independently
- Closing one window doesn't affect others
- Original image window remains fully functional

---

## 5. Save As Functionality

### Feature Description
Save edited images from zoom windows in multiple formats.

### Access Methods
- **Menu**: 檔案(&F) → 另存新檔
- **Shortcut**: Ctrl+S
- **Toolbar**: Save button

### Supported Formats
1. **PNG** (*.png)
   - Lossless compression
   - Supports transparency
   - Best for graphics with sharp edges

2. **JPEG** (*.jpg, *.jpeg)
   - Lossy compression
   - Smaller file size
   - Best for photographs

3. **BMP** (*.bmp)
   - Uncompressed
   - Large file size
   - Maximum quality

### Features
- File dialog for location and name selection
- Format selection dropdown
- Success/error message feedback
- Saves all edits made with brush tool
- Original image remains unchanged

---

## 6. Brush/Paint Tool

### Feature Description
Draw directly on zoomed images with customizable brush.

### Activation
- **Button**: "畫筆模式" (Brush Mode) in toolbar
- **Type**: Toggle button (checkable)
- **Feedback**: 
  - Cursor changes to cross (+) when active
  - Status bar shows "畫筆模式已啟用" when enabled
  - Status bar shows "畫筆模式已關閉" when disabled

### Brush Controls

#### 1. Brush Size
- **Control**: Spinbox in toolbar
- **Label**: "筆刷大小" (Brush Size)
- **Range**: 1 to 50 pixels
- **Default**: 5 pixels
- **Use**: Adjust stroke width

#### 2. Brush Color
- **Button**: "選擇顏色" (Select Color)
- **Dialog**: Standard Qt color picker
- **Default**: Red
- **Features**:
  - Full RGB color selection
  - Recent colors saved
  - Custom colors supported

### Drawing Features
- **Continuous Drawing**: Hold left mouse button and drag
- **Separate Strokes**: Release and click again for new stroke
- **Smooth Lines**: Anti-aliased rendering
- **Round Caps**: Smooth line endpoints
- **Permanent**: Changes saved to image

### Use Cases
- Annotating images
- Highlighting areas of interest
- Marking defects or features
- Adding notes or labels
- Artistic editing
- Quality control marking

---

## Architecture and Design

### Main Window (IMG Class)
**Responsibilities:**
- Image loading and display
- Mouse event handling
- Region selection tracking
- Grayscale value calculation
- Zoom window creation

**Key Methods:**
- `mouseMoveEvent()`: Grayscale display and selection update
- `mousePressEvent()`: Selection start
- `mouseReleaseEvent()`: Selection complete and zoom window creation
- `paintEvent()`: Selection rectangle rendering

### Zoom Window (ZoomWindow Class)
**Responsibilities:**
- Zoomed image display
- Brush tool management
- Image editing
- File saving

**Key Methods:**
- `setImage()`: Set and scale image
- `toggleDrawMode()`: Enable/disable brush
- `selectBrushColor()`: Color picker
- `setBrushSize()`: Adjust brush size
- `mouseMoveEvent()`: Drawing implementation
- `saveImageAs()`: File save dialog

### Integration
- Main window creates zoom windows dynamically
- Each zoom window is independent QMainWindow
- Qt's parent-child relationship ensures proper cleanup
- Signal-slot mechanism for UI updates

---

## User Workflow Examples

### Workflow 1: Basic Image Inspection
1. Open application
2. Load image (Ctrl+O)
3. Move mouse to see grayscale values
4. Identify interesting region
5. Select region by dragging
6. Choose 3x zoom
7. Inspect details in zoom window

### Workflow 2: Image Annotation
1. Load image
2. Select region requiring annotation
3. Choose appropriate zoom (2-5x)
4. Enable brush mode
5. Select color (e.g., red for errors, green for OK)
6. Adjust brush size as needed
7. Draw annotations
8. Save annotated image
9. Repeat for other regions

### Workflow 3: Detailed Analysis
1. Load large image
2. Select first region of interest
3. Zoom 5-10x for pixel-level view
4. Use grayscale display to analyze values
5. Mark findings with brush
6. Save marked region
7. Return to main window
8. Select next region
9. Repeat process

### Workflow 4: Comparison
1. Load image
2. Select region A, zoom 3x
3. Note findings
4. Return to main window (don't close zoom)
5. Select region B (same size), zoom 3x
6. Compare regions side by side
7. Annotate differences in each window
8. Save both for reporting

---

## Technical Specifications

### Image Processing
- **Library**: Qt 5 QImage
- **Color Space**: RGB
- **Grayscale Formula**: Qt's qGray() (standard luminance)
- **Scaling Algorithm**: Qt::SmoothTransformation (high quality)

### Coordinate Systems
- **Widget Coordinates**: Relative to widget origin
- **Global Coordinates**: Screen-based (for cross-widget operations)
- **Image Coordinates**: Pixel-based in original image

### Performance
- **Real-time Updates**: Mouse tracking at screen refresh rate
- **Image Scaling**: GPU-accelerated when available
- **Memory Management**: Qt's implicit sharing
- **Drawing Performance**: Direct QPainter on QImage

### Compatibility
- **Qt Version**: Qt 5.x
- **C++ Standard**: C++17
- **Platforms**: Linux, Windows, macOS (anywhere Qt runs)
- **Image Formats**: All Qt-supported (PNG, JPEG, BMP, GIF, etc.)

---

## Best Practices

### For Users
1. **Select appropriate zoom levels**: 2-3x for general use, 5-10x for details
2. **Use appropriate brush sizes**: Small (1-5) for precision, large (20-50) for coverage
3. **Save frequently**: Changes only saved when you explicitly save
4. **Close zoom windows**: When done to free memory
5. **Use keyboard shortcuts**: Ctrl+O, Ctrl+S for efficiency

### For Developers
1. **Memory management**: Qt's parent-child handles cleanup
2. **Coordinate mapping**: Always use Qt's mapping functions
3. **Image operations**: Use Qt's built-in transformations
4. **Thread safety**: All GUI operations on main thread
5. **Error handling**: Check image validity before operations

---

## Future Enhancement Possibilities

While not currently implemented, the architecture supports:
- Undo/redo for brush strokes
- Additional drawing tools (shapes, text)
- Zoom level adjustment after window creation
- Pan functionality for large zoomed images
- Side-by-side comparison view
- Image filters and effects
- Histogram display
- Batch processing
- Export to different formats with quality settings

---

## Conclusion

The implementation successfully adds powerful image inspection and annotation capabilities to the Qt Image Processor. The features work together seamlessly:

1. **Grayscale display** helps identify regions of interest
2. **Region selection** makes it easy to zoom specific areas
3. **Custom zoom** provides flexibility for different use cases
4. **Independent windows** enable multi-region comparison
5. **Brush tool** allows annotation and marking
6. **Save functionality** preserves work for later use

All features are designed to be intuitive and follow Qt best practices for a native desktop application experience.

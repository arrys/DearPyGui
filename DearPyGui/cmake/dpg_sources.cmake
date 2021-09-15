﻿
set(MARVEL_SOURCES

	"$<$<PLATFORM_ID:Windows>:src/core/Modules/mvModule_DearPyGui.cpp>"
	"$<$<PLATFORM_ID:Linux>:src/core/Modules/mvModule_DearPyGui.cpp>"
	"$<$<PLATFORM_ID:Darwin>:src/core/Modules/mvModule_DearPyGui.mm>"

	"src/core/PythonUtilities/mvPyObject.cpp"
	"src/core/PythonUtilities/mvPythonTranslator.cpp"
	"src/core/PythonUtilities/mvPythonParser.cpp"
	"src/core/PythonUtilities/mvPythonExceptions.cpp"
	"src/core/PythonUtilities/mvGlobalIntepreterLock.cpp"
	"src/core/PythonUtilities/mvPythonTypeChecker.cpp"

	"$<$<PLATFORM_ID:Windows>:src/platform/Windows/mvWindowsViewport.cpp>"
	"$<$<PLATFORM_ID:Windows>:src/platform/Windows/mvUtilities.cpp>"

	"$<$<PLATFORM_ID:Darwin>:src/platform/Apple/mvAppleViewport.mm>"
	"$<$<PLATFORM_ID:Darwin>:src/platform/Apple/mvUtilities.mm>"

	"$<$<PLATFORM_ID:Linux>:src/platform/Linux/mvUtilities.cpp>"
	"$<$<PLATFORM_ID:Linux>:src/platform/Linux/mvLinuxViewport.cpp>"

	"src/core/mvBuffer.cpp"
	"src/core/mvEvents.cpp"
	"src/core/mvContext.cpp"
	"src/core/mvViewport.cpp"
	"src/core/mvProfiler.cpp"
	"src/core/mvCallbackRegistry.cpp"

	"src/core/CustomImGuiWidgets/mvKnobCustom.cpp"
	"src/core/CustomImGuiWidgets/mvLoadingIndicatorCustom.cpp"

	"src/core/Theming/mvFontManager.cpp"
	
	"src/core/Tooling/mvToolManager.cpp"
	"src/core/Tooling/mvToolWindow.cpp"
	"src/core/Tooling/mvAboutWindow.cpp"
	"src/core/Tooling/mvDocWindow.cpp"
	"src/core/Tooling/mvMetricsWindow.cpp"
	"src/core/Tooling/mvStyleWindow.cpp"
	"src/core/Tooling/mvDebugWindow.cpp"
	"src/core/Tooling/mvLayoutWindow.cpp"

	"src/core/AppItems/mvAppItemState.cpp"
	"src/core/AppItems/mvAppItem.cpp"
	"src/core/AppItems/mvItemRegistry.cpp"

	"src/core/AppItems/textures/mvRawTexture.cpp"
	"src/core/AppItems/textures/mvStaticTexture.cpp"
	"src/core/AppItems/textures/mvDynamicTexture.cpp"
	"src/core/AppItems/textures/mvTextureRegistry.cpp"

	"src/core/AppItems/basic/mvMenuItem.cpp"
	"src/core/AppItems/basic/mvInputText.cpp"
	"src/core/AppItems/basic/mvText.cpp"
	"src/core/AppItems/basic/mvSliderSingle.cpp"
	"src/core/AppItems/basic/mvSliderMulti.cpp"
	"src/core/AppItems/basic/mvImage.cpp"
	"src/core/AppItems/basic/mvImageButton.cpp"
	"src/core/AppItems/basic/mvRadioButton.cpp"
	"src/core/AppItems/basic/mvListbox.cpp"
	"src/core/AppItems/basic/mvCombo.cpp"
	"src/core/AppItems/basic/mvCheckbox.cpp"
	"src/core/AppItems/basic/mvButton.cpp"
	"src/core/AppItems/basic/mvSelectable.cpp"
	"src/core/AppItems/basic/mvTabButton.cpp"
	"src/core/AppItems/basic/mvDragSingle.cpp"
	"src/core/AppItems/basic/mvDragMulti.cpp"
	"src/core/AppItems/basic/mvInputSingle.cpp"
	"src/core/AppItems/basic/mvInputMulti.cpp"

	"src/core/AppItems/colors/mvColorButton.cpp"
	"src/core/AppItems/colors/mvColorEdit.cpp"
	"src/core/AppItems/colors/mvColorPicker.cpp"
	"src/core/AppItems/colors/mvColorMap.cpp"
	"src/core/AppItems/colors/mvColorMapButton.cpp"
	"src/core/AppItems/colors/mvColorMapRegistry.cpp"
	"src/core/AppItems/colors/mvColorMapScale.cpp"
	"src/core/AppItems/colors/mvColorMapSlider.cpp"

	"src/core/AppItems/misc/mvItemPool.cpp"
	"src/core/AppItems/misc/mvProgressBar.cpp"
	"src/core/AppItems/misc/mvSeparator.cpp"
	"src/core/AppItems/misc/mvSpacer.cpp"

	"src/core/AppItems/themes/mvTheme.cpp"
	"src/core/AppItems/themes/mvThemeComponent.cpp"
	"src/core/AppItems/themes/mvThemeColor.cpp"
	"src/core/AppItems/themes/mvThemeStyle.cpp"

	"src/core/AppItems/containers/mvTemplateRegistry.cpp"
	"src/core/AppItems/containers/mvStage.cpp"
	"src/core/AppItems/containers/mvCollapsingHeader.cpp"
	"src/core/AppItems/containers/mvGroup.cpp"
	"src/core/AppItems/containers/mvChild.cpp"
	"src/core/AppItems/containers/mvTooltip.cpp"
	"src/core/AppItems/containers/mvTab.cpp"
	"src/core/AppItems/containers/mvTabBar.cpp"
	"src/core/AppItems/containers/mvMenu.cpp"
	"src/core/AppItems/containers/mvMenuBar.cpp"
	"src/core/AppItems/containers/mvTreeNode.cpp"
	"src/core/AppItems/containers/mvWindowAppItem.cpp"
	"src/core/AppItems/containers/mvDragPayload.cpp"
	"src/core/AppItems/containers/mvFilterSet.cpp"
	"src/core/AppItems/containers/mvClipper.cpp"
	"src/core/AppItems/containers/mvViewportMenuBar.cpp"

	"src/core/AppItems/tables/mvTable.cpp"
	"src/core/AppItems/tables/mvTableColumn.cpp"
	"src/core/AppItems/tables/mvTableRow.cpp"
	"src/core/AppItems/tables/mvTableCell.cpp"

	"src/core/AppItems/custom/mvDatePicker.cpp"
	"src/core/AppItems/custom/mvTimePicker.cpp"
	"src/core/AppItems/custom/mvSlider3D.cpp"
	"src/core/AppItems/custom/mvKnob.cpp"
	"src/core/AppItems/custom/mvLoadingIndicator.cpp"

	"src/core/AppItems/drawing/mvDrawlist.cpp"
	"src/core/AppItems/drawing/mvDrawLine.cpp"
	"src/core/AppItems/drawing/mvDrawArrow.cpp"
	"src/core/AppItems/drawing/mvDrawTriangle.cpp"
	"src/core/AppItems/drawing/mvDrawCircle.cpp"
	"src/core/AppItems/drawing/mvDrawEllipse.cpp"
	"src/core/AppItems/drawing/mvDrawBezierCubic.cpp"
	"src/core/AppItems/drawing/mvDrawBezierQuadratic.cpp"
	"src/core/AppItems/drawing/mvDrawQuad.cpp"
	"src/core/AppItems/drawing/mvDrawRect.cpp"
	"src/core/AppItems/drawing/mvDrawText.cpp"
	"src/core/AppItems/drawing/mvDrawPolygon.cpp"
	"src/core/AppItems/drawing/mvDrawPolyline.cpp"
	"src/core/AppItems/drawing/mvDrawImage.cpp"
	"src/core/AppItems/drawing/mvDrawLayer.cpp"
	"src/core/AppItems/drawing/mvViewportDrawlist.cpp"
	
	"src/core/AppItems/composite/mvFileDialog.cpp"
	"src/core/AppItems/composite/mvFileExtension.cpp"

	"src/core/AppItems/nodes/mvNodeEditor.cpp"
	"src/core/AppItems/nodes/mvNode.cpp"
	"src/core/AppItems/nodes/mvNodeAttribute.cpp"
	"src/core/AppItems/nodes/mvNodeLink.cpp"

	"src/core/AppItems/fonts/mvFontRegistry.cpp"
	"src/core/AppItems/fonts/mvFont.cpp"
	"src/core/AppItems/fonts/mvFontRange.cpp"
	"src/core/AppItems/fonts/mvFontChars.cpp"
	"src/core/AppItems/fonts/mvFontRangeHint.cpp"
	"src/core/AppItems/fonts/mvCharRemap.cpp"
	
	"src/core/AppItems/plots/mvSubPlots.cpp"
	"src/core/AppItems/plots/mvPlot.cpp"
	"src/core/AppItems/plots/mvPlotLegend.cpp"
	"src/core/AppItems/plots/mvPlotAxis.cpp"
	"src/core/AppItems/plots/mvAreaSeries.cpp"
	"src/core/AppItems/plots/mvDragPoint.cpp"
	"src/core/AppItems/plots/mvDragLine.cpp"
	"src/core/AppItems/plots/mvAnnotation.cpp"
	"src/core/AppItems/plots/mvSimplePlot.cpp"
	"src/core/AppItems/plots/mvLineSeries.cpp"
	"src/core/AppItems/plots/mvScatterSeries.cpp"
	"src/core/AppItems/plots/mvStemSeries.cpp"
	"src/core/AppItems/plots/mvStairSeries.cpp"
	"src/core/AppItems/plots/mvBarSeries.cpp"
	"src/core/AppItems/plots/mvErrorSeries.cpp"
	"src/core/AppItems/plots/mvInfiniteLineSeries.cpp"
	"src/core/AppItems/plots/mvHeatSeries.cpp"
	"src/core/AppItems/plots/mvImageSeries.cpp"
	"src/core/AppItems/plots/mvPieSeries.cpp"
	"src/core/AppItems/plots/mvShadeSeries.cpp"
	"src/core/AppItems/plots/mvLabelSeries.cpp"
	"src/core/AppItems/plots/mvCandleSeries.cpp"
	"src/core/AppItems/plots/mvHistogramSeries.cpp"
	"src/core/AppItems/plots/mv2dHistogramSeries.cpp"

	"src/core/AppItems/handlers/mvHandlerRegistry.cpp"
	"src/core/AppItems/handlers/mvKeyDownHandler.cpp"
	"src/core/AppItems/handlers/mvKeyPressHandler.cpp"
	"src/core/AppItems/handlers/mvKeyReleaseHandler.cpp"
	"src/core/AppItems/handlers/mvMouseMoveHandler.cpp"
	"src/core/AppItems/handlers/mvMouseWheelHandler.cpp"
	"src/core/AppItems/handlers/mvMouseClickHandler.cpp"
	"src/core/AppItems/handlers/mvMouseDoubleClickHandler.cpp"
	"src/core/AppItems/handlers/mvMouseDownHandler.cpp"
	"src/core/AppItems/handlers/mvMouseReleaseHandler.cpp"
	"src/core/AppItems/handlers/mvMouseDragHandler.cpp"

	"src/core/AppItems/widget_handlers/mvHoverHandler.cpp"
	"src/core/AppItems/widget_handlers/mvItemHandlerRegistry.cpp"
	"src/core/AppItems/widget_handlers/mvActiveHandler.cpp"
	"src/core/AppItems/widget_handlers/mvFocusHandler.cpp"
	"src/core/AppItems/widget_handlers/mvVisibleHandler.cpp"
    "src/core/AppItems/widget_handlers/mvActivatedHandler.cpp"
    "src/core/AppItems/widget_handlers/mvDeactivatedHandler.cpp"
    "src/core/AppItems/widget_handlers/mvEditedHandler.cpp"
    "src/core/AppItems/widget_handlers/mvDeactivatedAfterEditHandler.cpp"
    "src/core/AppItems/widget_handlers/mvToggledOpenHandler.cpp"
    "src/core/AppItems/widget_handlers/mvClickedHandler.cpp"
	"src/core/AppItems/widget_handlers/mvResizeHandler.cpp"

	"src/core/AppItems/values/mvValueRegistry.cpp"
	"src/core/AppItems/values/mvIntValue.cpp"
	"src/core/AppItems/values/mvBoolValue.cpp"
	"src/core/AppItems/values/mvInt4Value.cpp"
	"src/core/AppItems/values/mvFloatValue.cpp"
	"src/core/AppItems/values/mvFloat4Value.cpp"
	"src/core/AppItems/values/mvStringValue.cpp"
	"src/core/AppItems/values/mvDoubleValue.cpp"
	"src/core/AppItems/values/mvDouble4Value.cpp"
	"src/core/AppItems/values/mvColorValue.cpp"
	"src/core/AppItems/values/mvFloatVectValue.cpp"
	"src/core/AppItems/values/mvSeriesValue.cpp"

	# imnodes
	"vendor/imnodes/imnodes.cpp"

	# implot
	"vendor/implot/implot.cpp"
	"vendor/implot/implot_items.cpp"
	"vendor/implot/implot_demo.cpp"

	# ImGuiFileDialog
	"../Dependencies/ImGuiFileDialog/ImGuiFileDialog/ImGuiFileDialog.cpp"

	# imgui
	"../Dependencies/imgui/misc/cpp/imgui_stdlib.cpp"
	"../Dependencies/imgui/imgui.cpp"
	"../Dependencies/imgui/imgui_demo.cpp"
	"../Dependencies/imgui/imgui_draw.cpp"
	"../Dependencies/imgui/imgui_widgets.cpp"
	"../Dependencies/imgui/imgui_tables.cpp"
	"$<$<PLATFORM_ID:Windows>:../Dependencies/imgui/misc/freetype/imgui_freetype.cpp>"
	"$<$<PLATFORM_ID:Windows>:../Dependencies/imgui/backends/imgui_impl_win32.cpp>"
	"$<$<PLATFORM_ID:Windows>:../Dependencies/imgui/backends/imgui_impl_dx11.cpp>"
	"$<$<PLATFORM_ID:Darwin>:../Dependencies/imgui/backends/imgui_impl_metal.mm>"
	"$<$<PLATFORM_ID:Darwin>:../Dependencies/imgui/backends/imgui_impl_glfw.cpp>"
	"$<$<PLATFORM_ID:Darwin>:../Dependencies/imgui/misc/freetype/imgui_freetype.cpp>"
	"$<$<PLATFORM_ID:Linux>:../Dependencies/imgui/examples/libs/gl3w/GL/gl3w.c>"
	"$<$<PLATFORM_ID:Linux>:../Dependencies/imgui/backends/imgui_impl_glfw.cpp>"
	"$<$<PLATFORM_ID:Linux>:../Dependencies/imgui/backends/imgui_impl_opengl3.cpp>"
)

set(MARVEL_INCLUDE_DIR

	"vendor/implot"
	"vendor/stb"
	"vendor/imnodes"
	"src/"
	"src/core"
	"src/core/CustomImGuiWidgets"
	"src/core/Modules"
	"src/core/AppItems"
	"src/core/PythonUtilities"
	"src/core/Theming"
	"src/core/Tooling"
	"$<$<PLATFORM_ID:Windows>:${CMAKE_SOURCE_DIR}/DearPyGui/vendor/dirent/>"
	"../Dependencies/ImGuiFileDialog/ImGuiFileDialog/"
	"../Dependencies/ImGuiFileDialog/"
	"../Dependencies/glfw/include/"
	"../Dependencies/glfw/deps/"
	"../Dependencies/imgui/"
	"../Dependencies/imgui/misc/freetype/"
	"../Dependencies/imgui/backends/"
	"../Dependencies/imgui/examples/libs/gl3w"
	"../Dependencies/cpython/"
	"../Dependencies/cpython/Include/"
	"../Dependencies/cpython/build/debug/"
	"$<$<PLATFORM_ID:Windows>:${CMAKE_SOURCE_DIR}/Dependencies/cpython/PC/>"
	"$<IF:$<CONFIG:Release>,${CMAKE_SOURCE_DIR}/Dependencies/cpython/build/release/,${CMAKE_SOURCE_DIR}/Dependencies/cpython/build/debug/>"
)

# CannyEdgeDetector

![Canny edge detector](https://upload.wikimedia.org/wikipedia/commons/thumb/2/20/%C3%84%C3%A4retuvastuse_n%C3%A4ide.png/500px-%C3%84%C3%A4retuvastuse_n%C3%A4ide.png)

https://en.wikipedia.org/wiki/Canny_edge_detector


<br><br>

## Short description

Finds edges

<br><br>

## Inputs

|Name|Description|Optional|
|:----|:-----------|:-------|
|INPUT|The iage input|No|

<br><br>

## Outputs

|Name|Description|
|:----|:-----------|
|EDGES|Edge magnitude|
|MAXIMA|Orientation estimate|
|OUTPUT|Final edges|
|dx|Gradient estimation and categorization|
|dy|Gradient estimation and categorization|
|dGx|Filter kernel|
|dGy|Filter kernel|

<br><br>

## Parameters

|Name|Description|Type|Default value|
|:----|:-----------|:----|:-------------|
|scale|Scale parameter|float|1.0|
|T0|First threshold|float|100|
|T1|Second threshold|float|200|
|T2|Third threshold|float|800|

<br><br>
## Long description
Module that applies the Canny edge detector to an image. This edge detector works in five steps:
    1. Gradient Estimation using a Gaussian edge detector.
    2. Orientation Classification.
    3. Nonmaximum Supression.
    4. Hysteresis Thresholding.
    This is not exactly the algorithm as described by Canny (the edge filter is different and edges are only found at a single scale) but it is reasonably similar.

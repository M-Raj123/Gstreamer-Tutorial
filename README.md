# Gstreamer-Tutorial
a simple programs using gstreamer framework libraries which i've practiced


##  generate a GStreamer pipeline diagram

Install dot :
```bash
$ sudo apt-get install graphviz
```

Add this line after all the elements are created and linked
```bash
GST_DEBUG_BIN_TO_DOT_FILE(pipeline, GST_DEBUG_GRAPH_SHOW_ALL, "pipeline")
```

run the app like:
```bash
$ GST_DEBUG_DUMP_DOT_DIR=. ./application
```

export dot file to png:
```bash
$ dot -Tpng pipeline.dot > pipeline.png
```

open the pipeline.png
```bash
$ eog pipeline.png
```

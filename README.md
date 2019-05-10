An emulation of the Mr. Black DoubleChorus pedal. The algorithm used is described here: 
https://www.mrblackpedals.com/blogs/straight-jive/7147476-secrets-of-tone-what-makes-the-doublechorus-so-epically-rad

If you want the plugin, download and unzip the component.zip file (mac) or vst.zip file (windows), and put it in your plugin folder.

The plugin itself is easy to use, and installs like any other VST or Component.

If you want to look at the code, all the interesting (i.e. non auto-generated) stuff lives in the Source directory, and the bulk of the signal processing happens in PluginProcessor.cpp. 

To compile the code, you'll need JUCE (https://shop.juce.com/get-juce), and you might need to know a little about how to use JUCE too. Ask me if you want!! but few people are probably reading this and I imagine even fewer are trying to compile this themselves.

Finally, a big shoutout to Marc Wilhite's Stereo Chorus project, which was a great resource when I was getting started: https://github.com/marcwilhite/StereoChorus/blob/master/Source/CustomLookAndFeel.cpp

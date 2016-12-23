# lumihoop-app
Tracking &amp; mapping for the Lumihoop project

<a href="https://vimeo.com/196621657">![](https://res.cloudinary.com/thibault-maekelbergh/image/upload/v1482490669/Lumihoop/Screenshot_2016-12-23_11.56.11.png)</a>

## Brief
> As final assignment in your last programming course, you will make an installation for kids, to be used in the youth film festival's medialab.
You'll work in groups of two. Use at least one of the technologies we treated troughout the course (openframeworks, arduino, makeymakey, kinect, leap, …).

## Concept
@kevinmeyvaert and I teamed up to create an interactive basketball-like installation that could be used in any space as long as you had the hardware at hand.
You can view the project teaser on Vimeo: https://vimeo.com/196621657

### Hardware & software used
* Kinect (v1)
* Beamer
* A cool led beachball 🏐
* Openframeworks application (ofxGui, ofxKinect, ofxXmlSettings, [ofxSocketIO](https://github.com/soixantecircuits/ofxSocketIO))

![](https://res.cloudinary.com/thibault-maekelbergh/image/upload/v1482491531/Lumihoop/IMG_4406.jpg)

This application needs to be used in conjuction with the [lumihoop-client](https://github.com/thibmaek/lumihoop-client).

Tracking itself is done by creating and reading depth from a pointcloud. As this was our first interactive/experimental/native installation we were quite surprised with the tracking accuracy from the pointcloud.
We built in a debug UI in this application so it could easily be used in any space or any surface (wall, floor, ceiling) as long as you set the distance and Z scale.

![](https://res.cloudinary.com/thibault-maekelbergh/image/upload/v1482491535/Lumihoop/Schermafdruk_2016-12-21_17.29.29.png)

> Special thanks to @wouterverweirder for helping us out and @devinehowest for the fun project opportunity!

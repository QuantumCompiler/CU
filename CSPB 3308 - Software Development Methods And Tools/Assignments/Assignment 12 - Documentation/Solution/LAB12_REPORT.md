# Lab 12 Report

## Part 1

- The url for the project that I am reviewing is: [Flutter](https://github.com/flutter/flutter)
- The name of this resource is called Flutter.
- Flutter is a UI toolkit for building natively compiled applications for mobile, web, and desktop from a single codebase. Developers can build applications for Android, iOS, Windows, Mac, Linux, Google Fuchsia, and the web from a single codebase. Flutter is an open-source project that is developed by Google.
- The types of documentation that are present in this repository are:
    - Markdown
    - HTML

## Part 2

This repository includes links to various different forms of documentation. But, inside the repo itself are examples of Flutter projects. In the examples directory, there is a README file that documents what some of the files / directories are for a project. This is seen best as a screenshot below:

<p align="center">
    <img src="images/Flutter Examples.png" width=750>
</p>

Some of these link to nested READMES, but this README that is found above gives a broad overview of the examples that are found in the directory.

Here are some changes that I would make to this documentation:

- Give a broad overview of the file structure that is found in a Flutter project.
- Give a brief description of how to run one of these flutter examples without having to make a new project for this example alone.
- Give a brief description of what each example does and what it is used for.


## Part 3

A good example of inline documentation can be found in the texture example:

~~~
  // Set the color of the texture.
  Future<void> setColor(int r, int g, int b) async {
    await channel.invokeMethod('setColor', <int>[r, g, b]);
  }
~~~

For someone like myself who is use to the widget tree that is found in flutter, most of the semantics of a page or widget is pretty simple. But for some functions that are found in the texture example, it can be confusing as to what a function is doing.

This is a good example of inline documentation because it explains what the function does in a simple comment. This is helpful for someone who is not familiar with the codebase and is trying to understand what a function does.

## Part 4

There really isn't a lot of examples of bad documentation found in this repo. But one example that I find to be kind of confusing that could use some improvement can be seen below:

<p align="center">
    <img src="images/Flutter Bad Example.png" width=750>
</p>

This documentation that can be found in the texture example is very, very minimalistic. I think that this could be improved by adding a brief description of what the texture example does and what it is used for. For example, why would someone want to use textures in Flutter? What does one typically use textures for? These are questions that could be answered in the documentation.

## Part 5

The main reason why I picked this repo for this lab is because this documentation is what I thumbed through when I was first learning Flutter. This repo provides a link to how to actually install Flutter on your machine, which is crucial when learning a new framework:

- [Install Flutter](https://docs.flutter.dev/get-started/install) - This link provides a step-by-step guide on how to install Flutter on your machine.

On top of this, this repo also provides a link to the broader documentation that is found on the Flutter website:

- [Flutter Documentation](https://docs.flutter.dev/) - This link provides a link to the broader documentation that is found on the Flutter website.

## Part 6

Flutter uses its own testing framework called Flutter Test. This is a testing framework that is used to test Flutter applications. Flutter provides its own documentation on how to get started with its testing framework:

- [Flutter Testing](https://flutter.dev/docs/testing)

## Part 7

Overall I believe the documentation for Flutter is really good. It provides a lot of examples and links to the broader documentation that is found on the Flutter website. The documentation is very easy to read and understand. The only thing that I would change is to provide a brief description of what each example does and what it is used for. This would be helpful for someone who is new to Flutter and is trying to understand what each example does.

I referenced this documentation when I was first learning Flutter and I found it to be very helpful. I think that this documentation is very well done and provides a lot of examples that are helpful for someone who is new to Flutter, as I was once that person :).
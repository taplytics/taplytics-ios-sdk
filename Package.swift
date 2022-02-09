// swift-tools-version:5.3
import PackageDescription

let package = Package(
    name: "Taplytics",
    platforms: [
        .iOS(.v10), .tvOS(.v10)
    ],
    products: [
        .library(
            name: "Taplytics",
            targets: ["Taplytics", "Taplytics_tvOS"]
        )
    ],
    targets: [
        .binaryTarget(
            name: "Taplytics",
            path: "./Taplytics.xcframework"
        ),
        .binaryTarget(
            name: "Taplytics_tvOS",
            path: "./Taplytics_tvOS.xcframework"
        )
    ]
)


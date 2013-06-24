using System;
using System.Collections.Generic;
using System.Linq;
using Fbx;

namespace Sample1_NodeNamePrinter
{
    /// <summary>
    /// Opens the sample file and pretty-prints the node names, attribute types, and pose information.
    /// </summary>
    class Program
    {
        static void Main(string[] args)
        {
            //
            // Create an instance of the manager and load in the .fbx scene file.
            //

            var manager = Manager.Create();
            var ioSettings = IoSettings.Create(manager);
            var importer = Importer.Create(manager);

            importer.Initialize("humanoid.fbx", ioSettings);

            var scene = Scene.Create(manager);

            importer.Import(scene);

            //
            // Extract node data and print.
            //

            var stack = new Stack<Tuple<Node, int>>();
            stack.Push(new Tuple<Node, int>(scene.GetRootNode(), 1));

            while (stack.Any())
            {
                var t = stack.Pop();
                var node = t.Item1;
                var inset = t.Item2;

                var attribute = node.Attribute == null ? "None" : node.Attribute.AttributeType.ToString();
                var format = String.Format("{0} - {1}", node.Name, attribute);

                Console.WriteLine(new String(' ', inset) + format);

                for (var i = 0; i < node.ChildCount; i++)
                {
                    stack.Push(new Tuple<Node, int>(node.GetChild(i), inset + 1));
                }
            }

            //
            // Clean up the resources used by manager and associated objects.
            //

            Console.ReadKey();

            manager.Dispose();
        }
    }
}

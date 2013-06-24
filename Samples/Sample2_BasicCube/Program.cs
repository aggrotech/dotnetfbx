using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using Fbx;
using SlimDX;
using SlimDX.D3DCompiler;
using SlimDX.DXGI;
using SlimDX.Direct3D11;
using SlimDX.Windows;
using Buffer = SlimDX.Direct3D11.Buffer;
using Resource = SlimDX.Direct3D11.Resource;

namespace Sample2_BasicCube
{
    /// <summary>
    /// Loads in and spins a cube.
    /// </summary>
    static class Program
    {
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);

            var form = new Form {Width = 640, Height = 480, Text = "Sample 2: Basic Cube"};

            //
            // Load cube!
            //

            var manager = Manager.Create();
            var importer = Importer.Create(manager);
            var ioSettings = IoSettings.Create(manager);
            importer.Initialize("cube.fbx", ioSettings);

            var scene = Scene.Create(manager);
            importer.Import(scene);

            var rootNode = scene.GetRootNode();

            var cube = rootNode.GetChild(0);

            var vertices = cube.MeshAttribute.ControlPoints;
            var indices = new List<int>();

            for (var i = 0; i < cube.MeshAttribute.PolygonCount; i++)
            {
                for (var j = 0; j < 3; j++)
                {
                    indices.Add(cube.MeshAttribute.GetPolygonVertex(i, j));
                }
            }

            //
            // Initialize SlimDX and fill the vertex and index buffers with cube data.
            //

            var description = new SwapChainDescription
            {
                BufferCount = 1,
                IsWindowed = true,
                Usage = Usage.RenderTargetOutput,
                ModeDescription = new ModeDescription(0, 0, new Rational(60, 1), Format.R8G8B8A8_UNorm),
                SampleDescription = new SampleDescription(1, 0),
                Flags = SwapChainFlags.AllowModeSwitch,
                SwapEffect = SwapEffect.Discard,
                OutputHandle = form.Handle
            };

            SlimDX.Direct3D11.Device device;
            SwapChain swapChain;
            SlimDX.Direct3D11.Device.CreateWithSwapChain(DriverType.Hardware, DeviceCreationFlags.None, description, out device, out swapChain);

            var context = device.ImmediateContext;

            using (var factory = swapChain.GetParent<Factory>())
            {
                factory.SetWindowAssociation(form.Handle, WindowAssociationFlags.IgnoreAltEnter);
            }

            var viewport = new Viewport(0, 0, form.Width, form.Height);
            context.Rasterizer.SetViewports(viewport);

            RenderTargetView backbufferView;

            using (var resource = Resource.FromSwapChain<Texture2D>(swapChain, 0))
            {
                backbufferView = new RenderTargetView(device, resource);
            }

            context.OutputMerger.SetTargets(backbufferView);

            VertexShader vertexShader;
            PixelShader pixelShader;

            ShaderSignature signature;

            using (var bytecode = ShaderBytecode.CompileFromFile("triangle.fx", "VShader", "vs_4_0", ShaderFlags.None, EffectFlags.None))
            {
                vertexShader = new VertexShader(device, bytecode);
                signature = ShaderSignature.GetInputSignature(bytecode);
            }
    
            using (var bytecode = ShaderBytecode.CompileFromFile("triangle.fx", "PShader", "ps_4_0", ShaderFlags.None, EffectFlags.None))
            {
                pixelShader = new PixelShader(device, bytecode);
            }
    
            //
            // Fill vertex and index buffers with cube data.
            //

            var vertDs = new DataStream(vertices.Length * 12, true, true);
            var iDs = new DataStream(indices.Count * 2, true, true);

            foreach (var vert in vertices)
            {
                vertDs.Write(new Vector3((float)vert.x, (float)vert.y, (float)vert.z));
            }

            vertDs.Position = 0;

            var vertexBuffer = new Buffer(device, vertDs, (int)vertDs.Length, ResourceUsage.Default, BindFlags.VertexBuffer, CpuAccessFlags.None, ResourceOptionFlags.None, 0);

            foreach (var index in indices)
            {
                iDs.Write((short)index);
            }

            iDs.Position = 0;

            var indexBuffer = new Buffer(device, iDs, (int) iDs.Length, ResourceUsage.Default, BindFlags.IndexBuffer, CpuAccessFlags.None, ResourceOptionFlags.None, 0);

            var elements = new[] { new InputElement("POSITION", 0, Format.R32G32B32_Float, 0) };

            context.InputAssembler.InputLayout = new InputLayout(device, signature, elements);
            context.InputAssembler.PrimitiveTopology = PrimitiveTopology.TriangleList;
            
            context.InputAssembler.SetVertexBuffers(0, new VertexBufferBinding(vertexBuffer, 12, 0));
            context.InputAssembler.SetIndexBuffer(indexBuffer, Format.R16_UInt, 0);

            context.VertexShader.Set(vertexShader);
            context.PixelShader.Set(pixelShader);

            RasterizerStateDescription rsd = new RasterizerStateDescription()
            {
                CullMode = CullMode.None,
                DepthBias = 0,
                DepthBiasClamp = 0.0f,
                FillMode = FillMode.Wireframe,
                IsAntialiasedLineEnabled = false,
                IsDepthClipEnabled = false,
                IsFrontCounterclockwise = false,
                IsMultisampleEnabled = false,
                IsScissorEnabled = false,
                SlopeScaledDepthBias = 0.0f
            };

            context.Rasterizer.State = RasterizerState.FromDescription(device, rsd);

            form.Resize += (o, e) =>
            {
                backbufferView.Dispose();

                swapChain.ResizeBuffers(2, 0, 0, Format.R8G8B8A8_UNorm, SwapChainFlags.AllowModeSwitch);
                using (var resource = Resource.FromSwapChain<Texture2D>(swapChain, 0))
                    backbufferView = new RenderTargetView(device, resource);

                context.OutputMerger.SetTargets(backbufferView);
            };

            var watch = new Stopwatch();

            watch.Start();
            
            //
            // Go!
            //
            MessagePump.Run(form, () =>
            {
                context.ClearRenderTargetView(backbufferView, new Color4(0.5f, 0.5f, 1.0f));

                var deg = 0.0174532925f*(watch.ElapsedMilliseconds / 10);

                var cbStream = new DataStream(4 * 4 * 4, true, true);
                cbStream.Write(Matrix.Identity * Matrix.Scaling(0.5f, 0.5f, 0.5f) * Matrix.RotationX(deg) * Matrix.RotationY(deg));

                cbStream.Position = 0;

                var cb = new Buffer(device, cbStream, 16 * 4, ResourceUsage.Default, BindFlags.ConstantBuffer, CpuAccessFlags.None,ResourceOptionFlags.None, 0);

                context.VertexShader.SetConstantBuffer(cb, 0);

                context.DrawIndexed(indices.Count, 0, 0);
                swapChain.Present(0, PresentFlags.None);

                cb.Dispose();
            });

            Application.Exit();
        }
    }
}
